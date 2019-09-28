#include "linear.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>

#include "boost/timer/timer.hpp"


using std::vector;
using std::string;
using std::find;
using std::cout;
using std::endl;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<double> sec;
typedef std::minstd_rand generator;
typedef std::uniform_int_distribution<> distribution;

int time_find(vector<int> data, int iterations)
{
    cout << "std::find" << endl;

    generator g;
    distribution d(0, (int)data.size() - 1);

    boost::timer::auto_cpu_timer t;

    int did_find = 0;

    for (int i = 0; i < iterations; i++)
    {
        // pick a random value from the data range
        int value = d(g);

        // search for that value
        vector<int>::iterator found = std::find(data.begin(), data.end(), value);

        // use the value so it's not optimized away
        if (found != data.end())
        {
            did_find++;
        }
    }

    return did_find;
}

int time_linear(vector<int> data, int iterations)
{
    cout << "search::linear" << endl;

    generator g;
    distribution d(0, (int)data.size() - 1);

    boost::timer::auto_cpu_timer t;

    int did_find = 0;

    for (int i = 0; i < iterations; i++)
    {
        // pick a random value from the data range
        int value = d(g);

        // search for that value
        vector<int>::iterator found = search::linear(data.begin(), data.end(), value);

        // use the value so it's not optimized away
        if (found != data.end())
        {
            did_find++;
        }
    }

    return did_find;
}

int run_test(int vectorSize, int iterations)
{
    vector<int> data(vectorSize);
    for (int i = 0; i < (int)data.size(); i++)
    {
        data[i] = i;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(data.begin(), data.end(), std::default_random_engine(seed));

    int found = 0;

    for (int i = 0; i < 10; i++)
    {
        found += time_find(data, iterations);
        found += time_linear(data, iterations);
    }

    return found;
}