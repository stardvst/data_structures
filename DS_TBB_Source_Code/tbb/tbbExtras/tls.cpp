#include "tbb\tbb.h"
#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

long parallel_sum(const std::vector<int>& values) {
    typedef tbb::blocked_range<std::vector<int>::const_iterator> range_type;

    tbb::combinable<long> sums;

    tbb::parallel_for(range_type(values.begin(), values.end()),
        [&sums](range_type range) {
            sums.local() += std::accumulate(range.begin(), range.end(), 0); 
    });

    return sums.combine(std::plus<long>());
}

void combinable_loop() {
    std::vector<int> data(200000);
    std::generate(data.begin(), data.end(), rand);
    
    long expected = std::accumulate(data.begin(), data.end(), 0);
    long actual = parallel_sum(data);

    std::cout << "Expected: " << expected << std::endl
              << "Actual: " << actual << std::endl
              << "Result: " << (expected == actual) << std::endl;
}

template<typename Func>
tbb::tick_count::interval_t time(Func func) {
    auto start = tbb::tick_count::now();
    func();

    return tbb::tick_count::now() - start;
}

void combine_set(std::vector<int> &data, std::set<int> &unique) {
    typedef tbb::blocked_range<std::vector<int>::const_iterator> range_type;
    tbb::combinable<std::set<int>> uniques;

    tbb::parallel_for(range_type(data.begin(), data.end()),
        [&uniques](range_type range) {
        uniques.local().insert(range.begin(), range.end());
    });

    uniques.combine_each([&unique](std::set<int>& tls_set) {
        unique.insert(tls_set.begin(), tls_set.end());
    });
}

void combine_set_enumerable(std::vector<int> &data, std::set<int> &unique) {
    typedef tbb::blocked_range<std::vector<int>::const_iterator> range_type;
    tbb::enumerable_thread_specific<std::set<int>> uniques;

    tbb::parallel_for(range_type(data.begin(), data.end()),
        [&uniques](range_type range) {
        uniques.local().insert(range.begin(), range.end());
    });

    for (auto tls_set : uniques) {
        unique.insert(tls_set.begin(), tls_set.end());
    }
}


bool are_equal(std::set<int>& left, std::set<int>& right, std::set<int>& other) {
    if (!(left.size() == right.size() == other.size())) {
        return false;
    }

    if (right.size() == 0) {
        return false;
    }

    for (int li : left) {
        right.erase(li);
        other.erase(li);
    }

    return (right.size() == 0) && (other.size() == 0);
}


void combinable_unique() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(1, 500000);

    std::vector<int> data(1500000);
    std::generate(data.begin(), data.end(), [&uni, &rng]{ return uni(rng); });

    std::set<int> linear_unique;
    std::set<int> parallel_unique;
    std::set<int> enumerable_unique;

    auto linear_time = time([&data, &linear_unique](){
        linear_unique.insert(data.begin(), data.end());
    });

    auto enumerable_time = time([&data, &enumerable_unique](){
        combine_set_enumerable(data, enumerable_unique);
    });

    auto parallel_time = time([&data, &parallel_unique](){
        combine_set(data, parallel_unique);
    });

    std::cout
        << linear_unique.size() << " "
        << linear_time.seconds() << " "
        << parallel_time.seconds() << " "
        << enumerable_time.seconds() << " "
        << 1 - (parallel_time.seconds() / linear_time.seconds()) << "% "
        << are_equal(linear_unique, parallel_unique, enumerable_unique) << std::endl;
}
