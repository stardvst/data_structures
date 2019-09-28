#include "boost/range/algorithm/binary_search.hpp"
#include "boost/range/algorithm/find.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include <cassert>

void boost_binarysearch_test()
{
    std::string str = "SEARCH ALGORITHM";
    std::vector<char> data(str.begin(), str.end());

    // binary search requires the data to be sorted
    std::sort(data.begin(), data.end());

    // true
    boost::range::binary_search(data, ' ');
    boost::range::binary_search(data, 'R');

    // false
    boost::range::binary_search(data, 'Z');
    boost::range::binary_search(data, '!');
}

void boost_linear_search()
{
    std::string str = "SEARCH ALGORITHM";
    std::vector<char> data(str.begin(), str.end());

    std::vector<char>::iterator r;
    r = boost::range::find(data, 'R');
}