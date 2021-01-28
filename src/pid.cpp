//
//  pid.cpp
//  E-CVT SW
//
//  Created by Daniel Wang on 2020-11-21.
//  Copyright © 2020 Daniel Wang. All rights reserved.
//

#include "pid.hpp"

int pid::pid_task(float desired_value, float actual_value){
 
    float error = desired_value - actual_value;
    float integral = integral_prior + error * iteration_time;
    float derivative = (error - error_prior) / iteration_time;
    float output = KP*error + KI*integral + KD*derivative + bias;
    error_prior = error;
    integral_prior = integral;
    motor(output);
    return output;

    //sleep(iteration_time)
    
}
