#include "bubble.h"
#include <iostream>
#include <functional>
#include <string>


void bubble_sort_default()
{
    std::string data = "SORTING ALGORITHM";
    sorting::bubble(data.begin(), data.end());

    // " AGGHIILMNOORRSTT"
    std::cout << data << std::endl;
}

void bubble_sort_custom()
{
    std::string data = "SORTING ALGORITHM";
    sorting::bubble(data.begin(), data.end(), std::greater<char>());

    // "TTSRROONMLIIHGGA "
    std::cout << data << std::endl;
}

void bubble_tests()
{
    bubble_sort_default();
    bubble_sort_custom();
}