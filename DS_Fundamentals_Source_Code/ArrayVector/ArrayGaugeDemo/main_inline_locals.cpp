#include "gauge_reading.h"
#include "gauge_simulator.h"
#include <iostream>

void main_inline_locals()
{
    gauge_simulator simulator(
        0,            // low end of the gauge values
        500,        // high end of the gauge values
        time(0),    // the time of the first reading
        5);            // number of seconds to add to each subsequent reading

    gauge_reading *reading1 = simulator.current();
    gauge_reading *reading2 = simulator.current();
    gauge_reading *reading3 = simulator.current();
    gauge_reading *reading4 = simulator.current();
    gauge_reading *reading5 = simulator.current();

    print_reading(reading1);
    print_reading(reading2);
    print_reading(reading3);
    print_reading(reading4);
    print_reading(reading5);
}