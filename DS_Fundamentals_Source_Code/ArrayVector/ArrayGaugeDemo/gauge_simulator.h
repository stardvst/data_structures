#pragma once
#include <random>
#include "gauge.h"
#include "gauge_reading.h"

class gauge_simulator : public gauge
{
private:
    std::default_random_engine _rng_engine;
    std::uniform_int_distribution<int> *_rng;
    time_t _start_time;
    int _seconds_between_reads;
    int _reads;

public:
    gauge_simulator(int min, int max, time_t start, int seconds);

    gauge_reading* current();
};

