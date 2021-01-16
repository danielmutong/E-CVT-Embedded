//
//  sensor.cpp
//  E-CVT SW
//
//  Created by Daniel Wang on 2020-11-21.
//  Copyright © 2020 Daniel Wang. All rights reserved.
//
#include <sensor.hpp>
#include <testdata.h>
int random_index;

void motor(float output){
    //cout << "motor running" << output << endl;
    trace_printf("motor running : %f \n", output);

}


float getRPM(){
    //float rpm;
    //cout << "enter rpm: " << endl;
    //cin >> rpm;
    //return rpm;

	return testdata[random_index][0];
      
}

float getThrottle(){
    //float throttle;
    //cout << "enter Throttle: " << endl;
   // cin >> throttle;
   // return throttle;
   // trace_printf("motor running : %f \n", testdata[random_index][1]);

	return testdata[random_index][1];


}

float getTorque(){
    //trace_printf("motor running : %f \n", testdata[random_index][2]);

	return testdata[random_index][2];

}
