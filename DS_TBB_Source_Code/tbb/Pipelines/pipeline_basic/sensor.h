#pragma once

#include <random>

struct sensor_reading {
    sensor_reading(int sid, int rid, int value)
        : sensor(sid), reading_id(rid), reading(value) {}
    
    int sensor;
    int reading_id;
    int reading;
};

class sensor {
    const int _id;
    int _last_reading;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

public:
    sensor(int id)
        : _id(id), _last_reading(0), gen(rd()), dis(0, 100) { }

    sensor_reading* read() {
        return new sensor_reading(_id, _last_reading++, static_cast<int>(dis(gen)));
    }
};