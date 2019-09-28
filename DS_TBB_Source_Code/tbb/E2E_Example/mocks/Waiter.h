#pragma once

#include <random>
#include <chrono>
#include "tbb/tbb.h"

class BusyWaiter {
    std::mt19937 generator;

public:
    BusyWaiter() : generator(
        static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())) {}

    void Wait(int minMs, int maxMs) {
        std::uniform_int_distribution<int> distribution(minMs, maxMs);

        int waitMs = distribution(generator);
        tbb::tick_count start = tbb::tick_count::now();

        while (true) {
            int waited = int((tbb::tick_count::now() - start).seconds() * 1000);
            if (waited >= waitMs) {
                return;
            }
        }

    }
};

class SleepWait {
    std::mt19937 generator;

public:
    SleepWait() : generator(
        static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())) {}

    void Wait(int minMs, int maxMs) {
        std::uniform_int_distribution<int> distribution(minMs, maxMs);

        double waitMs = distribution(generator);

        tbb::this_tbb_thread::sleep(tbb::tick_count::interval_t(waitMs / 1000));
    }
};

class WorkSimulator {
    SleepWait sleeper;
    BusyWaiter busy;
public:

    void Sleep(int minMs, int maxMs) {
        sleeper.Wait(minMs, maxMs);
    }

    void Busy(int minMs, int maxMs) {
        busy.Wait(minMs, maxMs);
    }
};

extern WorkSimulator Worker;