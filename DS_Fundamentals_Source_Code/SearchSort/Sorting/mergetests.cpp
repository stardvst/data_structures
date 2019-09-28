#include "merge.h"
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <cassert>

void merge_sort_default()
{
    std::string data = "SORTING ALGORITHM";
    sorting::merge(data.begin(), data.end());

    // " AGGHIILMNOORRSTT"
    std::cout << data << std::endl;
}

void merge_sort_custom()
{
    std::string data = "SORTING ALGORITHM";
    sorting::merge(data.begin(), data.end(), std::greater<char>());

    // "TTSRROONMLIIHGGA "
    std::cout << data << std::endl;
}

std::string msort(std::string data)
{
    sorting::merge(data.begin(), data.end());
    return data;
}

bool msorted(std::string data)
{
    return std::is_sorted(data.begin(), data.end());
}

void mtest(std::string data)
{
    data = msort(data);
    assert(msorted(data));
}

void merge_tests()
{
    mtest("38215467");

    mtest("1234");
    mtest("4321");
    mtest("4444");
    mtest("11211");
    mtest("");
    mtest("1");

    merge_sort_default();
    merge_sort_custom();
}
