#pragma once

#include"tbb/tbb.h"
#include "sensor.h"
#include <iostream>

class output_filter : public tbb::filter {
public:
    output_filter() : filter(tbb::filter::mode::serial_out_of_order) { }

    void* operator()(void *r) {
        sensor_reading* reading = static_cast<sensor_reading*>(r);
        
        std::cout << "[" << reading->sensor << "] "
            << reading->reading_id << ": " << reading->reading 
            << std::endl;

        delete reading;

        return nullptr;
    }
};