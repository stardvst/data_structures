#include "linear.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using std::vector;
using std::string;
using std::find;
using std::cout;
using std::endl;

void lineartest()
{
    string str = "SEARCH ALGORITHM";
    vector<char> data(str.begin(), str.end());

    char toFind = 'R';
    for (
        vector<char>::iterator r = search::linear(data.begin(), data.end(), toFind);
        r != data.end();
    r = search::linear(r + 1, data.end(), toFind)
        ) {
        cout << "Found at index " << r - data.begin() << endl;
    }
}