#include "tbb/tbb.h"
#include <iostream>
#include <array>

struct PrintValue {
    void operator()(const tbb::blocked_range<int>& range) const {
        for(int current = range.begin(); current != range.end(); ++current) {
            std::cout << current << ' ';
        }
    }
};

struct PrintValueArray {
    void operator()(const tbb::blocked_range<int*>& range) const {
        for (int* current = range.begin(); current != range.end(); ++current) {
            std::cout << *current << ' ';
        }
    }
};

void blocked_range_example() {

    tbb::blocked_range<int> range(0, 10);

    for (int current = range.begin(); current != range.end(); ++current) {
        std::cout << current << ' ';
    }

    std::cout << std::endl;
}

void blocked_range_example_values() {

const int length = 10;
int values[length] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

tbb::blocked_range<int*> range(values, values + length);
    
for (int* current = range.begin(); current != range.end(); ++current) {
    std::cout << *current << ' ';
}

    std::cout << std::endl;
}

void print_range(tbb::blocked_range<int*>& range) {
    for (int* current = range.begin(); current != range.end(); ++current) {
        std::cout << *current << ' ';
    }

    std::cout << std::endl;
}

void blocked_range2d_example() {
    const int rows = 10;
    const int cols = 20;
    int values[rows][cols] = {};

    tbb::blocked_range2d<int> range(0, rows, 0, cols);

    for (size_t x = range.rows().begin();
        x != range.rows().end(); ++x){
        for (size_t y = range.cols().begin();
            y != range.cols().end(); ++y) {
            // do something with values[x][y];
        }
    }
}

void blocked_range_split() {
    const int length = 10;
    int values[length] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

    tbb::blocked_range<int*> range(values, values + length);
    tbb::blocked_range<int*> range_right(range, tbb::proportional_split());

    // 10 .. 50
    print_range(range);
    // 60 .. 100
    print_range(range_right);
}

