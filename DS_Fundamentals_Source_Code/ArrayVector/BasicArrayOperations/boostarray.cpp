#include <boost/array.hpp>
#include <iostream>

using namespace boost;

void boostarray()
{
    array<int, 10> data = { 0 };

    try
    {
        // access one beyond the last element
        data.at(10);
    }
    catch (std::out_of_range)
    {
        std::cout << "Out of range" << std::endl;
    }

}