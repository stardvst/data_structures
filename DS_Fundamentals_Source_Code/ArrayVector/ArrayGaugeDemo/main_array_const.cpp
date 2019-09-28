#include "gauge_reading.h"
#include "gauge_simulator.h"
#include <iostream>

void main_array_const()
{
    gauge_simulator simulator(0, 500, time(0), 5);
    const int count = 5;

    gauge_reading* readings[count];
    for (int i = 0; i < count; i++)
    {
        readings[i] = simulator.current();
    }

    for (int i = 0; i < count; i++)
    {
        std::cout << "Reading " << i << ": " 
                  << readings[i]->reading 
                  << " at " << readings[i]->when << std::endl;
    }
}