#include "gauge_reading.h"
#include "gauge_simulator.h"
#include <iostream>

void main_array_init_syntax()
{
    gauge_simulator simulator(0, 500, time(0), 5);

    gauge_reading* readings[5] = 
    {
        simulator.current(),
        simulator.current(),
        simulator.current(),
        simulator.current(),
        simulator.current()
    };

    for (int i = 0; i < 5; i++)
    {
        std::cout << "Reading " << i << ": " << readings[i]->reading << " at " << readings[i]->when << std::endl;
    }
}