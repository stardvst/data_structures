#include "insertion.h"
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <cassert>

void insertion_sort_default()
{
    std::string data = "SORTING ALGORITHM";
    sorting::insertion(data.begin(), data.end());

    // " AGGHIILMNOORRSTT"
    std::cout << data << std::endl;
}

void insertion_sort_custom()
{
    std::string data = "SORTING ALGORITHM";
    sorting::insertion(data.begin(), data.end(), std::greater<char>());

    // "TTSRROONMLIIHGGA "
    std::cout << data << std::endl;
}

std::string sort(std::string data)
{
    sorting::insertion(data.begin(), data.end());
    return data;
}

bool sorted(std::string data)
{
    return std::is_sorted(data.begin(), data.end());
}

void test(std::string data)
{
    data = sort(data);
    assert(sorted(data));
}

void insertion_tests()
{
    test("1234");
    test("4321");
    test("4444");
    test("11211");
    test("");
    test("1");

    insertion_sort_default();
    insertion_sort_custom();
}