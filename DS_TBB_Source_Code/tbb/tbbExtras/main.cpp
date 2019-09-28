#include"tbb/tbb.h"
#include "examples.h"
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
#include <atomic>

template<class Func>
double time_it(Func function){
    const int iterations = 5;

    auto start = tbb::tick_count::now();


    for (int i = 0; i < iterations; i++) {
        function();
    }

    auto elapsed = tbb::tick_count::now() - start;
    return elapsed.seconds() / iterations;
}

namespace cache_test {
    void cache_test();
}

void run_all()
{
    cache_test::cache_test();
}

int main()
{
    srand(time(NULL));
    run_all();
}

