//
//  LookUp.hpp
//  E-CVT SW
//
//  Created by Daniel Wang on 2020-11-18.
//  Copyright © 2020 Daniel Wang. All rights reserved.
//

#ifndef LookUp_hpp
#define LookUp_hpp

#include "Table.h"
class LookUp {
private:
    float output;
    float key1;

public:
    LookUp(){}
    ~LookUp(){};
    
    /*
     This method finds and returns the value associated with the key in a map
     */
    int findkey(float key);
};

#endif /* LookUp_hpp */
