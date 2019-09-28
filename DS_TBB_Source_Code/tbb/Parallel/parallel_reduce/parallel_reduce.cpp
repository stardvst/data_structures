#include "tbb/tbb.h"
#include <iostream>
#include <functional>
#include <numeric>


template<class T>
struct Summer {
    T sum;

    Summer() : sum(0) { }
    Summer(Summer<T>& rs, tbb::split) : sum(rs.sum) { }

    void operator()(const tbb::blocked_range<T*>& range) {
        T temp = sum;
        for (T* value = range.begin(); value != range.end(); value++) {
            temp += *value;
        }
        sum = temp;
    }

    void join(Summer<T> &rhs) { sum += rhs.sum; }
};

template<class T>
struct RangeSum {
    T sum;

    RangeSum() : sum(0) { }
    RangeSum(RangeSum<T>& rs, tbb::split) : sum(rs.sum) { }

    void operator()(const tbb::blocked_range<T*>& range) {
        sum = std::accumulate(range.begin(), range.end(), sum);
    }

    void join(RangeSum<T> &rhs) { sum += rhs.sum; }
};


void parallel_reduce_example()
{
    int values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    RangeSum<int> summer;
    tbb::parallel_reduce(tbb::blocked_range<int*>(values, values+10), summer);

    std::cout << summer.sum << std::endl;
}

void parallel_reduce_lambda_example()
{
    int values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    int result = tbb::parallel_reduce(
        tbb::blocked_range<int*>(values, values + 10),
        0,
        [](const tbb::blocked_range<int*>& r, int value)->int {
            return std::accumulate(r.begin(), r.end(), value);
        },
        std::plus<int>());
}