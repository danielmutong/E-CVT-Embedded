//
//  sensor.cpp
//  E-CVT SW
//
//  Created by Daniel Wang on 2020-11-21.
//  Copyright © 2020 Daniel Wang. All rights reserved.
//
#include <sensor.hpp>
#include <testdata.h>
int count;

void motor(float output){
    trace_printf("motor running : %f \n", output);

}


float getRPM(){

	return testdata[count][0];
      
}

float getSheath(){


	return testdata[count][1];

}

int getThrottle(){
	return testdata[count][2];
}

