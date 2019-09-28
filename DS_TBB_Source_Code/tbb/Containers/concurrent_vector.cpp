#include "tbb/tbb.h"
#include <thread>
#include <iostream>

void concurrent_vector_basic() {

    tbb::concurrent_vector<int> values;

    auto add_values = [&values](int min, int max) {
        for (int i = min; i < max; i++) {
            values.push_back(i);
        }
    };

    std::thread threads[] = {
        std::thread(add_values, 1, 100000),
        std::thread(add_values, 100001, 200000),
    };

    for (std::thread& t : threads) {
        t.join();
    }
}

void concurrent_vector_grow_by() {
    tbb::concurrent_vector<int> values;

    auto grow_to_at_least = [&values](int growth) {
        values.grow_to_at_least(growth);
    };

    std::thread threads[] = {
        std::thread(grow_to_at_least, 250),
        std::thread(grow_to_at_least, 500),
    };

    for (std::thread& t : threads) {
        t.join();
    }

    // At least 500
    std::cout << values.size() << std::endl;
}

void concurrent_vector_range() {
    typedef tbb::concurrent_vector<int>::const_range_type range;

    tbb::concurrent_vector<int> values;

    for (int i = 0; i < 10000; i++) {
        values.push_back(i);
    }


    tbb::parallel_for(values.range(1000),
        [](const range& range) {
        std::cout << "parallel_for range size "
            << range.end() - range.begin()
            << std::endl;
    }
    );

}

