#include <array>
#include <iostream>

void stdarray()
{
    std::array<int, 10> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array<int, 10> equal_to = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::array<int, 10> less_than = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    std::array<int, 10> greater_than = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    
    // true
    std::cout << (data == equal_to) << std::endl;
    // false
    std::cout << (data != equal_to) << std::endl;

    // true
    std::cout << (less_than < data) << std::endl;
    // false
    std::cout << (data < less_than) << std::endl;

    // true
    std::cout << (greater_than > data) << std::endl;
    // false
    std::cout << (data > greater_than) << std::endl;
}