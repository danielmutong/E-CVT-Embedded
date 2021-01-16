//
//  sensor.hpp
//  E-CVT SW
//
//  Created by Daniel Wang on 2020-11-21.
//  Copyright © 2020 Daniel Wang. All rights reserved.
//

#ifndef sensor_hpp
#define sensor_hpp
#include <stdio.h>
#include "diag/Trace.h"


void motor(float output);
float getRPM();
float getThrottle();
float getTorque();

extern int random_index;



#endif /* sensor_hpp */
