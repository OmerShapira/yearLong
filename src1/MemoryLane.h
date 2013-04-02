//
//  MemoryLane.h
//  yearLong
//
//  Created by Omer Shapira on 31/03/13.
//
//

#ifndef __yearLong__MemoryLane__
#define __yearLong__MemoryLane__
#define FILE_HEIGHT 500
#define FILE_WIDTH 50
#define CAR_DISTANCE 10

#include <iostream>
#include "Car.h"
#include "CarAccumulator.h"

class Lane {

public:
    std::vector<Car> movingCars;
    
};

#endif /* defined(__yearLong__MemoryLane__) */
