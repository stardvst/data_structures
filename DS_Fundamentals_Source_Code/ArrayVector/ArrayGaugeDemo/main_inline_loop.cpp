#include "gauge_reading.h"
#include "gauge_simulator.h"
#include <iostream>

void main_inline_loop()
{
    gauge_simulator simulator(
        0,            // low end of the gauge values
        500,        // high end of the gauge values
        time(0),    // the time of the first reading
        5);            // number of seconds to add to each subsequent reading

    for (int i = 0; i < 5; i++)
    {
        gauge_reading *reading = simulator.current();
        std::cout << "Reading " << i << ": " << reading->reading << " at " << reading->when << std::endl;
        delete reading;
    }
}