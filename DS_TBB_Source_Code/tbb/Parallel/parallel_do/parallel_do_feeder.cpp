#include "tbb/tbb.h"
#include <list>
#include <iostream>

struct PrintFeederValues {
    void operator()(int& value, 
                    tbb::parallel_do_feeder<int>& feeder) const {

        std::cout << value << ' ';

        if (value < 10) {
            feeder.add(value * 10);
        }
    }
};

void parallel_do_feeder_example()
{
    std::list<int> data = { 1, 2, 3, 4, 5 };

    tbb::parallel_do(data, PrintFeederValues());

    std::cout << std::endl;
}