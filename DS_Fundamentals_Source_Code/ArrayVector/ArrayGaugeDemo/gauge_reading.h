#pragma once
#include <ctime>
#include <iostream>

struct gauge_reading
{
    int reading;
    time_t when;
};


inline void print_reading(gauge_reading *reading)
{
    std::cout
        << reading->reading << " at " 
        << reading->when << std::endl;
}

