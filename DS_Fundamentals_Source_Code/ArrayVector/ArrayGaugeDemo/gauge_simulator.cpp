#include "gauge_simulator.h"
#include <chrono>


gauge_simulator::gauge_simulator(int min, int max, time_t start, int seconds)
{
    _rng_engine.seed(
        static_cast<unsigned long>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count()
        ));
    _rng = new std::uniform_int_distribution<int>(min, max);
    _start_time = start;
    _seconds_between_reads = seconds;
    _reads = 0;
}

gauge_reading* gauge_simulator::current()
{
    gauge_reading *reading = new gauge_reading();
    reading->reading = (*_rng)(_rng_engine);
    reading->when = _start_time + (_seconds_between_reads * _reads++);

    return reading;
}
