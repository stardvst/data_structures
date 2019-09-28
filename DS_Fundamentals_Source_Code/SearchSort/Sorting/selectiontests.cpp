#include "selection.h"
#include <iostream>
#include <functional>
#include <string>


void selection_sort_default()
{
    std::string data = "SORTING ALGORITHM";
    sorting::selection(data.begin(), data.end());

    // " AGGHIILMNOORRSTT"
    std::cout << data << std::endl;
}

void selection_sort_custom()
{
    std::string data = "SORTING ALGORITHM";
    sorting::selection(data.begin(), data.end(), std::greater<char>());

    // "TTSRROONMLIIHGGA "
    std::cout << data << std::endl;
}

void selection_tests()
{
    selection_sort_default();
    selection_sort_custom();
}