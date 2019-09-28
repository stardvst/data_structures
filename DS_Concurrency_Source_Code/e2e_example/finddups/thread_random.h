#pragma once

#include <random>
#include <memory>

class thread_random
{
private:
    std::random_device device;
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;

public:
    thread_random(int min, int max)
        : generator(device()), distribution(min, max)
    {

    }
    
    int next()
    {
        return distribution(generator);
    }
};