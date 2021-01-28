//
//  pid.hpp
//  E-CVT SW
//
//  Created by Daniel Wang on 2020-11-21.
//  Copyright © 2020 Daniel Wang. All rights reserved.
//


#ifndef pid_hpp
#define pid_hpp

#include <stdio.h>
#include "sensor.hpp"

class pid{
private:
    float KP;
    float KI;
    float KD;
    int error_prior;
    int integral_prior;
    int bias;
    int iteration_time;
    float error;
    float integral;
    float derivative;
    float output;
public:
    
    /*
     Constructor to initialize constants required for PID controller
     */
    pid(){
        KP = 1;
        KI = 0;
        KD = 0;
        error_prior = 0; integral_prior = 0; bias = 0; iteration_time = 500; error = 0; integral = 0; derivative = 0; output = 0;
    };
    
    /*
     This method calculates and returns the necessary adjustment based on the PID controller
     */
    int pid_task(float desired_value, float actual_value);

};
#endif /* pid_hpp */
