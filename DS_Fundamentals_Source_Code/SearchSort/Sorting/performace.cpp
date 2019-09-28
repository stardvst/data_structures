#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <chrono>

#include "bubble.h"
#include "insertion.h"
#include "selection.h"
#include "merge.h"
#include "quicksort.h"

using namespace sorting;

#define PERF(func) \
class func ## _Sorting { public: void operator() (std::vector<int> data) \
{ \
    clock_t before = clock(); \
    func(data.begin(), data.end()); \
    clock_t duration = clock() - before; \
    std::cout << #func << " " << duration << std::endl; \
}};


PERF(bubble);
PERF(insertion);
PERF(selection);
PERF(merge);
PERF(quicksort);

#define TEST(func, method) \
{ \
    func##_Sorting func##Test; \
    func##Test(method(15000));  \
}

std::vector<int> pathological(int count)
{
    std::vector<int> data(count);
    for (int i = count; i > 0; i--)
    {
        data.push_back(i);
    }

    return data;
}

std::vector<int> presorted(int count)
{
    std::vector<int> data(count);
    for (int i = 0; i < count; i++)
    {
        data.push_back(i);
    }

    return data;
}

std::vector<int> random(int count)
{
    std::default_random_engine engine;
    std::uniform_int_distribution<int> rng(0, count);

    engine.seed(
        static_cast<unsigned long>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
        ));

    std::vector<int> data(count);
    for (int i = 0; i < count; i++)
    {
        data.push_back(rng(engine));
    }

    return data;
}

void perfTests()
{
    std::cout << "random" << std::endl;
    TEST(bubble, random);
    TEST(insertion, random);
    TEST(selection, random);
    TEST(merge, random);
    TEST(quicksort, random);

    std::cout << "pathological" << std::endl;
    TEST(bubble, pathological);
    TEST(insertion, pathological);
    TEST(selection, pathological);
    TEST(merge, pathological);
    TEST(quicksort, pathological);

    std::cout << "presorted" << std::endl;
    TEST(bubble, presorted);
    TEST(insertion, presorted);
    TEST(selection, presorted);
    TEST(merge, presorted);
    TEST(quicksort, presorted);
}
