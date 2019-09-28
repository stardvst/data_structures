#include "gauge_reading.h"
#include "gauge_simulator.h"
#include <iostream>
#include <vector>

using std::vector;

void vector_readings()
{
    gauge_simulator simulator(0, 500, time(0), 5);

    vector<gauge_reading*> readings;

    for (int i = 0; i < 100; i++)
    {
        readings.push_back(simulator.current());
    }
}