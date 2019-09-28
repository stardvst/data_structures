#include "tbb/tbb.h"
#include <list>
#include <iostream>

struct PrintValue {
public:
    void operator()(int& value) const {
        std::cout << value;
    }
};

void parallel_do_serial()
{
    std::list<int> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int value : data)
    {
        std::cout << value << std::endl;
    }
}

void parallel_do_example()
{
    std::list<int> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    tbb::parallel_do(data, PrintValue());

    std::cout << std::endl;
}

void parallel_do_lambda_example()
{
    std::list<int> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    tbb::parallel_do(data, [=](int value)
    {
        std::cout << value;
    });

    std::cout << std::endl;
}