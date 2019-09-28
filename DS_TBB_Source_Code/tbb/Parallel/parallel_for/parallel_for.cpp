#include "tbb/tbb.h"
#include <iostream>
#include <vector>
#include <numeric>

struct PrintValues {
    void operator()(const tbb::blocked_range<int*>& range) const {
        for (int* i = range.begin(); i != range.end(); i++) {
            std::cout << *i;
        }
    }
};

class PrintIndexValues {
    int* values;
public:
    PrintIndexValues(int *values_) : values(values_) { }

    void operator()(const int index) const {
        std::cout << values[index];
    }
};

template<class T>
struct DoubleValues {
    void operator()(const tbb::blocked_range<T*>& range) const {
        for (T* value = range.begin(); value != range.end(); value++) {
            *value = *value * 2;
        }
    }
};

template<class T>
class DoubleValuesIndex {
    T* values;

public:
    DoubleValuesIndex(T* values_)
        : values(values_)
    {}

    void operator()(const int index) const {
        values[index] *= 2;
    }
};


void double_values_serial()
{
    int values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int i = 0; i < 10; i++)
    {
        values[i] *= 2;
    }
}

void print_values() {
    int values[] = { 1, 3, 5, 7, 9 };

    tbb::parallel_for(
        tbb::blocked_range<int*>(values, values + 5), 
        PrintValues());

//    tbb::parallel_for(0, 5, PrintIndexValues(values));
}

void parallel_for_double_values() {
    int values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    tbb::parallel_for(tbb::blocked_range<int*>(values, values+10), DoubleValues<int>());

    for (int v : values) {
        std::cout << v << " ";
    }

    std::cout << std::endl;
}

void parallel_for_double_index() {
    int values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    tbb::parallel_for(0, 10, DoubleValuesIndex<int>(values));

    for (int v : values) {
        std::cout << v << " ";
    }

    std::cout << std::endl;
}


void parallel_for_double_values_lambda() {
    int values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    tbb::parallel_for(tbb::blocked_range<int>(0, 9), 
        [&](const tbb::blocked_range<int>& range) {
        for (int i = range.begin(); i != range.end(); i++) {
            values[i] *= 2;
        }
    });

    for (int v : values) {
        std::cout << v << " ";
    }

    std::cout << std::endl;
}

void parallel_for_double_2d_values_lambda() {
    const int rows = 3;
    const int cols = 4;

    int values[3][4] = {
        { 0, 1, 2, 3 },
        { 4, 5, 6, 7 },
        { 8, 9, 10, 11 }
    };

    tbb::parallel_for(tbb::blocked_range2d<int>(0, rows, 0, cols),
        [&](const tbb::blocked_range2d<int>& range) {
        for (size_t x = range.rows().begin(); x != range.rows().end(); ++x){
            for (size_t y = range.cols().begin(); y != range.cols().end(); ++y) {
                values[x][y] = values[x][y] * 2;
            }
        }
    });

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            std::cout << values[row][col] << ' ';
        }
        std::cout << std::endl;
    }
}
