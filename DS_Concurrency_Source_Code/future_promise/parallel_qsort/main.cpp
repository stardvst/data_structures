#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include "parallel_qsort.h"

void main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(INT_MIN, INT_MAX);

    const int COUNT = 2000000;

    for (int x = 0; x < 10; x++)
    {
        std::vector<int> values;
        for (int i = 0; i < COUNT; i++)
        {
            values.push_back(dis(gen));
        }

        auto start = std::chrono::steady_clock::now();
        sorting::quicksort(values.begin(), values.end());
        auto end = std::chrono::steady_clock::now();

        std::cout << "Parallel" << std::endl;
        std::cout << "Sorted: " << std::is_sorted(values.begin(), values.end()) << std::endl;
        std::cout << "Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        values.clear();
        for (int i = 0; i < COUNT; i++)
        {
            values.push_back(dis(gen));
        }

        start = std::chrono::steady_clock::now();
        sorting::lquicksort(values.begin(), values.end());
        end = std::chrono::steady_clock::now();

        std::cout << "Linear" << std::endl;
        std::cout << "Sorted: " << std::is_sorted(values.begin(), values.end()) << std::endl;
        std::cout << "Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    }
}