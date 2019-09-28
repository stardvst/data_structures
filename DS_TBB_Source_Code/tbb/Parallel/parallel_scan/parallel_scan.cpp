#define _SCL_SECURE_NO_WARNINGS

#include "tbb/tbb.h"
#include <iostream>
#include <numeric>

template<class T>
class RunningSum {
    T sum;
    T* const running_sums;
public:
    RunningSum(T running_sums_[])
        : sum(0), running_sums(running_sums_) {}

    RunningSum(RunningSum& b, tbb::split)
        : running_sums(b.running_sums), sum(0) {}

    void operator()(const tbb::blocked_range<T*>& r, tbb::pre_scan_tag) {
        sum = std::accumulate<T*>(r.begin(), r.end(), sum, std::plus<T>());
    }

    void operator()(const tbb::blocked_range<T*>& r, tbb::final_scan_tag) {
        for (T* cur = r.begin(); cur < r.end(); ++cur) {
            *cur = (sum += *cur);
        }
    }

    void reverse_join(RunningSum& a)  { sum += a.sum; }

    void assign(RunningSum& b) { sum = b.sum; }
};

void parallel_scan_example() {

    int data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const int length = sizeof(data) / sizeof(data[0]);

    RunningSum<int> summer(data);

    tbb::parallel_scan(tbb::blocked_range<int*>(data, data + length), summer);

    for (int running : data) {
        std::cout << running << std::endl;
    }
}

void parallel_scan_serial_example() {
    const int length = 10;

    int data[length] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int running_sum[length];

    int temp = 0;
    for (int i = 0; i < length; ++i) {
        temp = temp + data[i];
        running_sum[i] = temp;
    }

    for (int running : running_sum) {
        std::cout << running << ' ';
    }
}
