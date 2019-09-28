#include "quicksort.h"
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <cassert>

void quicksort_sort_default()
{
    std::string data = "SORTING ALGORITHM";
    sorting::quicksort(data.begin(), data.end());

    // " AGGHIILMNOORRSTT"
    std::cout << data << std::endl;
}

void quicksort_sort_custom()
{
    std::string data = "SORTING ALGORITHM";
    sorting::quicksort(data.begin(), data.end(), std::greater<char>());

    // "TTSRROONMLIIHGGA "
    std::cout << data << std::endl;
}

std::string qsort(std::string data)
{
    sorting::quicksort(data.begin(), data.end());
    return data;
}

bool qsorted(std::string data)
{
    return std::is_sorted(data.begin(), data.end());
}

void qtest(std::string data)
{
    data = qsort(data);
    assert(qsorted(data));
}

void quicksort_tests()
{
    qtest("SORTING ALGORITHM");
    qtest("38215467");

    qtest("1234");
    qtest("4321");
    qtest("43214321");
    qtest("12344321");
    qtest("232343452341231");
    qtest("4444");
    qtest("11211");
    qtest("");
    qtest("1");

    quicksort_sort_default();
    quicksort_sort_custom();
}
