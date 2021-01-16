//
//  LookUp.hpp
//  E-CVT SW
//
//  Created by Daniel Wang on 2020-11-18.
//  Copyright © 2020 Daniel Wang. All rights reserved.
//

#ifndef LookUp_hpp
#define LookUp_hpp

#include <Table.h>
class LookUp {
private:
    float output;
    float key1;
    float key2;
public:
    LookUp(float val1, float val2){
        output = 0;
        key1 = val1;
        key2 = val2;
    }
    ~LookUp(){};
    
    int findkey();
};

#endif /* LookUp_hpp */
