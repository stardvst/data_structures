#include "tbb/tbb.h"
#include <list>
#include <iostream>

struct PrintValue {
public:
    void operator()(int& value) const {
        std::cout << value;
    }
};

void parallel_for_each_example()
{
    std::list<int> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    tbb::parallel_for_each(data.begin(), data.end(), PrintValue());

    std::cout << std::endl;
}

void parallel_for_each_lambda_example()
{
    std::list<int> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    tbb::parallel_for_each(data, [](int value)
    {
        std::cout << value;
    });

    std::cout << std::endl;
}