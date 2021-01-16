//
//  pid.hpp
//  E-CVT SW
//
//  Created by Daniel Wang on 2020-11-21.
//  Copyright © 2020 Daniel Wang. All rights reserved.
//

#ifndef pid_hpp
#define pid_hpp

#include <sensor.hpp>
#include <stdio.h>

class pid{
private:
    float KP = 1;
    float KI = 0;
    float KD = 0;
    int error_prior = 0;
    int integral_prior = 0;
    int bias = 0;
    int iteration_time = 500;
    float error = 0;
    float integral = 0;
    float derivative = 0;
    float output = 0;
public:
    
    pid(){};
    
    void pid_task(float desired_value, float actual_value);

};
#endif /* pid_hpp */
