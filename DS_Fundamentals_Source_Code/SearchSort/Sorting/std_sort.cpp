#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <functional>

void std_sort_default()
{
    std::string data = "SORTING ALGORITHM";
    std::sort(data.begin(), data.end());

    std::cout << data << std::endl;
}

void std_sort_custom()
{
    std::string data = "SORTING ALGORITHM";
    std::sort(data.begin(), data.end(), std::greater<char>());

    std::cout << data << std::endl;
}


