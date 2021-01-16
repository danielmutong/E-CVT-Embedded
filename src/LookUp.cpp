//
//  LookUp.cpp
//  E-CVT SW
//
//  Created by Daniel Wang on 2020-11-18.
//  Copyright © 2020 Daniel Wang. All rights reserved.
//

#include <LookUp.hpp>
#include <Table.h>


map mymap[200] = {
    {  0.0  ,  0.0  ,  100.0  },
    {  0.0  ,  25.0  ,  100.0  },
    {  0.0  ,  50.0  ,  100.0  },
    {  0.0  ,  75.0  ,  100.0  },
    {  0.0  ,  100.0  ,  100.0  },
    {  500.0  ,  0.0  ,  150.0  },
    {  500.0  ,  25.0  ,  350.0  },
    {  500.0  ,  50.0  ,  400.0  },
    {  500.0  ,  75.0  ,  450.0  },
    {  500.0  ,  100.0  ,  500.0  },
    {  750.0  ,  0.0  ,  75.0  },
    {  750.0  ,  25.0  ,  525.0  },
    {  750.0  ,  50.0  ,  600.0  },
    {  750.0  ,  75.0  ,  675.0  },
    {  750.0  ,  100.0  ,  750.0  },
    {  969.0  ,  0.0  ,  0.0  },
    {  969.0  ,  25.0  ,  705.6  },
    {  969.0  ,  50.0  ,  1075.2  },
    {  969.0  ,  75.0  ,  1209.6  },
    {  969.0  ,  100.0  ,  1344.0  },
    {  1187.5  ,  0.0  ,  0.0  },
    {  1187.5  ,  25.0  ,  555.8  },
    {  1187.5  ,  50.0  ,  1088.9  },
    {  1187.5  ,  75.0  ,  1429.2  },
    {  1187.5  ,  100.0  ,  1588.0  },
    {  1406.0  ,  0.0  ,  0.0  },
    {  1406.0  ,  25.0  ,  287.2  },
    {  1406.0  ,  50.0  ,  93.7  },
    {  1406.0  ,  75.0  ,  1476.9  },
    {  1406.0  ,  100.0  ,  1641.0  },
    {  1625.0  ,  0.0  ,  0.0  },
    {  1625.0  ,  25.0  ,  0.0  },
    {  1625.0  ,  50.0  ,  756.0  },
    {  1625.0  ,  75.0  ,  1356.3  },
    {  1625.0  ,  100.0  ,  1654.0  },
    {  1844.0  ,  0.0  ,  0.0  },
    {  1844.0  ,  25.0  ,  0.0  },
    {  1844.0  ,  50.0  ,  560.0  },
    {  1844.0  ,  75.0  ,  1209.9  },
    {  1844.0  ,  100.0  ,  1635.0  },
    {  2062.5  ,  0.0  ,  0.0  },
    {  2062.5  ,  25.0  ,  0.0  },
    {  2062.5  ,  50.0  ,  356.0  },
    {  2062.5  ,  75.0  ,  1029.6  },
    {  2062.5  ,  100.0  ,  1560.0  },
    {  2281.0  ,  0.0  ,  0.0  },
    {  2281.0  ,  25.0  ,  0.0  },
    {  2281.0  ,  50.0  ,  167.3  },
    {  2281.0  ,  75.0  ,  849.1  },
    {  2281.0  ,  100.0  ,  1464.0  },
    {  2500.0  ,  0.0  ,  0.0  },
    {  2500.0  ,  25.0  ,  0.0  },
    {  2500.0  ,  50.0  ,  0.0  },
    {  2500.0  ,  75.0  ,  682.5  },
    {  2500.0  ,  100.0  ,  1365.0  },
    };
int LookUp::findkey(){
    int i = 0;
 
    i = 0;
    int temp1, temp2;
    
    //finding key1
    for(i = 0; i < 200; i++){
        if(key1 <= mymap[i].rpm)
            break;
    }
    
    if(key1 == mymap[i].rpm)
           temp1 = key1;
    else{
    //comparing lower and upper bounds for key1
   
        if((key1 - mymap[i-1].rpm) > (mymap[i].rpm - key1))
            temp1 = mymap[i].rpm;
    
        else
            temp1 = mymap[i-1].rpm;
    }
    //finding key2
    for(i = 0; i < 200; i++){
        if(key2 <= mymap[i].throttle)
            break;

    }
    if(key2 == mymap[i].throttle)
        temp2 = key2;
    //comparing lower and upper bounds for key2
    else{
        if((key2 - mymap[i-1].throttle) > (mymap[i].throttle - key2))
            temp2 = mymap[i].throttle;
        else
            temp2 = mymap[i-1].throttle;
    }
    //finding final output based on key1 and key2
    for(i = 0; i < 200; i++){
        if(mymap[i].rpm == temp1 && mymap[i].throttle == temp2){
            output = mymap[i].output;
            break;
        }
    }
    return output;
}
