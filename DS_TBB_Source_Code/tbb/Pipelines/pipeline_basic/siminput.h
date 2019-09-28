#pragma once
#include "tbb/tbb.h"
#include <atomic>
#include "sensor.h"

class simulated_data_input_filter : public tbb::filter
{
    std::atomic<int> _remaining;
    sensor _sensor;

public:
    simulated_data_input_filter(int sensor_id, int count)
        : _remaining(count), _sensor(sensor_id), filter(tbb::filter::mode::serial_in_order)
    {}

    void* operator()(void*) {
        if (_remaining-- <= 0) {
            return nullptr;
        }

        return _sensor.read();
    }
};

