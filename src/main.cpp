/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Timer.h"
#include "BlinkLed.h"
#include "testdata.h"
#include <LookUp.hpp>
#include <pid.hpp>
#include <sensor.hpp>
#include <Table.h>
#include "control.hpp"

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 led blink sample (trace via DEBUG).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// Then demonstrates how to blink a led with 1 Hz, using a
// continuous loop and SysTick delays.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// Definitions visible only within this translation unit.
namespace
{
  // ----- Timing definitions -------------------------------------------------

  // Keep the LED on for 2/3 of a second.
  constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
  constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ
      - BLINK_ON_TICKS;
}

// ----- LED definitions ------------------------------------------------------

#if defined(STM32F401xE)

#warning "Assume a NUCLEO-F401RE board, PA5, active high."

// PA5
#define BLINK_PORT_NUMBER         (0)
#define BLINK_PIN_NUMBER          (5)
#define BLINK_ACTIVE_LOW          (false)

BlinkLed blinkLeds[1] =
  {
    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER, BLINK_ACTIVE_LOW },
  };

#elif defined(STM32F407xx)

#warning "Assume a STM32F4-Discovery board, PD12-PD15, active high."

#define BLINK_PORT_NUMBER         (3)
#define BLINK_PIN_NUMBER_GREEN    (12)
#define BLINK_PIN_NUMBER_ORANGE   (13)
#define BLINK_PIN_NUMBER_RED      (14)
#define BLINK_PIN_NUMBER_BLUE     (15)
#define BLINK_ACTIVE_LOW          (false)

BlinkLed blinkLeds[4] =
  {
    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_GREEN, BLINK_ACTIVE_LOW },
    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_ORANGE, BLINK_ACTIVE_LOW },
    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_RED, BLINK_ACTIVE_LOW },
    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_BLUE, BLINK_ACTIVE_LOW },
  };

#elif defined(STM32F411xE)

#warning "Assume a NUCLEO-F411RE board, PA5, active high."

#define BLINK_PORT_NUMBER         (0)
#define BLINK_PIN_NUMBER          (5)
#define BLINK_ACTIVE_LOW          (false)

BlinkLed blinkLeds[1] =
  {
    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER, BLINK_ACTIVE_LOW },
  };

#elif defined(STM32F429xx)

#warning "Assume a STM32F429I-Discovery board, PG13-PG14, active high."

#define BLINK_PORT_NUMBER         (6)
#define BLINK_PIN_NUMBER_GREEN    (13)
#define BLINK_PIN_NUMBER_RED      (14)
#define BLINK_ACTIVE_LOW          (false)

BlinkLed blinkLeds[2] =
  {
    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_GREEN, BLINK_ACTIVE_LOW },
    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_RED, BLINK_ACTIVE_LOW },
  };

#else

#warning "Unknown board, assume PA5, active high."

#define BLINK_PORT_NUMBER         (0)
#define BLINK_PIN_NUMBER          (5)
#define BLINK_ACTIVE_LOW          (false)

BlinkLed blinkLeds[1] =
  {
    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER, BLINK_ACTIVE_LOW },
  };

#endif

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#define CCM_RAM __attribute__((section(".ccmram")))

#define FPU_TASK_STACK_SIZE 256

#define MIN_SHEATH 15 // minimum sheath position before limit switch
#define MAX_SHEATH 80 // starting sheath position
#define SHIFT_DISPLACEMENT 0.3
#define MAX_RPM 3550
#define MAX_THROTTLE 100
StackType_t task1stack[FPU_TASK_STACK_SIZE] CCM_RAM;  // Put task stack in CCM
StaticTask_t task1 CCM_RAM;  // Put TCB in CCM
void task1func(void *) {
	count = 10;
	  pid test;
	  LookUp a;
	  int rpm = 0;
	  int measured_sheath = 0;
	  int ideal_sheath = 0;
	  int throttle = 0;
	  float sheath = MAX_SHEATH;
	  	trace_printf("engagement phase\n \n");

	  //engagement phase
	  while(rpm < MAX_RPM){
	    rpm = getRPM();
	    throttle = getThrottle();
	    //if full throttle
	    if(throttle == 100){
	      //using map to find the optimal sheath given a pid in the transient phase
	      ideal_sheath = a.findkey(rpm);
	      measured_sheath = getSheath();
	  	trace_printf("rpm: %u  - ideal sheath :%u - measured sheath: %u  \n", rpm, ideal_sheath, measured_sheath);

	      int pid_out = test.pid_task(ideal_sheath, measured_sheath);  //feeding measured sheath and ideal sheath into pid to find the adjustment
	      sheath = measured_sheath + pid_out;   //moving sheath based on pid difference
	  	trace_printf("new sheath:%f  \n \n", sheath);

	    }
	    count = count + 1;
	    vTaskDelay(2000);


	  }
	  	trace_printf("shift phase\n \n");

	  //Once we get to 3550 rpm, we enter the straight shift phase where we want to keep rpm constant
	  while(1){
	    rpm = getRPM();
	    throttle = getThrottle();
	    if(throttle == MAX_THROTTLE && (rpm) > MAX_RPM){
	      if(sheath > MIN_SHEATH){ //makes sure sheath position doesnt exceed kill switch limit
	    	trace_printf("upshifting \n");
			  trace_printf("rpm:%u  \n", rpm);

	    	motor(100);
	        sheath = sheath -  SHIFT_DISPLACEMENT; //used for modelling
		  	trace_printf("new sheath:%f  \n \n", sheath);

	      }

	    }
	    //load
	    else if( (rpm < MAX_RPM && throttle == MAX_THROTTLE) ){
	    	trace_printf("experiencing load \n");
	      ideal_sheath = a.findkey(rpm);
		  trace_printf("rpm:%u  \n", rpm);
	      measured_sheath = getSheath();
		  	trace_printf("ideal sheath :%u - measured sheath: %u  \n", ideal_sheath, measured_sheath);
	      //moving sheath based on pid difference
	      int pid_out = test.pid_task(ideal_sheath, measured_sheath);
	      sheath = measured_sheath + pid_out; //used for modelling
		  trace_printf("new sheath:%f  \n \n", sheath);

	    }
	    //down shift linearly
	    else if(throttle == 0){
	      trace_printf("downshifting \n");
		  trace_printf("rpm:%u  \n", rpm);

	      motor(-100);
	      sheath = sheath + SHIFT_DISPLACEMENT; //used for modelling
		  trace_printf("new sheath:%f  \n \n", sheath);
	    }
	    count = count + 1;
	    vTaskDelay(2000);

	  }

}

StackType_t task2stack[FPU_TASK_STACK_SIZE] CCM_RAM;  // Put task stack in CCM
StaticTask_t task2 CCM_RAM;  // Put TCB in CCM
void task2func(void *) {

	while(1){
		count = count + 0;
	    vTaskDelay(1);

	}

}




int
main(int argc, char* argv[])
{
	__disable_irq();
  // Send a greeting to the trace device (skipped on Release).
//  trace_puts("Hello Arm World!");

  // At this stage the system clock should have already been configured
  // at high speed.
//  trace_printf("System clock: %u Hz\n", SystemCoreClock);
  xTaskCreateStatic(task1func, "task1", FPU_TASK_STACK_SIZE, NULL, 2, task1stack, &task1);
  xTaskCreateStatic(task2func, "task2", FPU_TASK_STACK_SIZE, NULL, 1, task2stack, &task2);
 __enable_irq();
  vTaskStartScheduler();  // should never return
  for(;;);

  Timer timer;
  timer.start ();

  // Perform all necessary initialisations for the LEDs.
  for (size_t i = 0; i < (sizeof(blinkLeds) / sizeof(blinkLeds[0])); ++i)
    {
      blinkLeds[i].powerUp ();
    }

  uint32_t seconds = 0;

  for (size_t i = 0; i < (sizeof(blinkLeds) / sizeof(blinkLeds[0])); ++i)
    {
      blinkLeds[i].turnOn ();
    }

  // First second is long.
  timer.sleep (Timer::FREQUENCY_HZ);

  for (size_t i = 0; i < (sizeof(blinkLeds) / sizeof(blinkLeds[0])); ++i)
    {
      blinkLeds[i].turnOff ();
    }

  timer.sleep (BLINK_OFF_TICKS);

  ++seconds;
  trace_printf ("Second %u\n", seconds);

  if ((sizeof(blinkLeds) / sizeof(blinkLeds[0])) > 1)
    {
      // Blink individual LEDs.
      for (size_t i = 0; i < (sizeof(blinkLeds) / sizeof(blinkLeds[0])); ++i)
        {
          blinkLeds[i].turnOn ();
          timer.sleep (BLINK_ON_TICKS);

          blinkLeds[i].turnOff ();
          timer.sleep (BLINK_OFF_TICKS);

          ++seconds;
          trace_printf ("Second %u\n", seconds);
        }

      // Blink binary.
      while (1)
        {
          for (size_t l = 0; l < (sizeof(blinkLeds) / sizeof(blinkLeds[0]));
              ++l)
            {
              blinkLeds[l].toggle ();
              if (blinkLeds[l].isOn ())
                {
                  break;
                }
            }
          timer.sleep (Timer::FREQUENCY_HZ);

          ++seconds;
          trace_printf ("Second %u\n", seconds);
        }
      // Infinite loop, never return.
    }
  else
    {
      while (1)
        {
          blinkLeds[0].turnOn ();
          timer.sleep (BLINK_ON_TICKS);

          blinkLeds[0].turnOff ();
          timer.sleep (BLINK_OFF_TICKS);

          ++seconds;
          trace_printf ("Second %u\n", seconds);
        }
      // Infinite loop, never return.
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
