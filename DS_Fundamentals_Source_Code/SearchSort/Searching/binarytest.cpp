#include "binary.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>

using std::vector;
using std::string;
using std::find;
using std::cout;
using std::endl;

void binarytest()
{
    string str = "SEARCH ALGORITHM";
    vector<char> data(str.begin(), str.end());

    // binary search requires the data to be sorted
    std::sort(data.begin(), data.end());

    // true
    assert(true == search::binary_norec(data.begin(), data.end(), ' '));
    assert(true == search::binary_norec(data.begin(), data.end(), 'R'));

    // false
    assert(false == search::binary_norec(data.begin(), data.end(), 'Z'));
    assert(false == search::binary_norec(data.begin(), data.end(), '!'));
}