#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "vector.h"


void test_push_back()
{
    ads::vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    for (size_t i = 0; i < v.size(); i++)
    {
        if (i != v[i])
        {
            throw "test_push_back failed";
        }
    }
}

void test_push_front()
{
    ads::vector<int> v;
    for (int i = 99; i >= 0; i--)
    {
        v.push_front(i);
    }

    if (100 != v.size())
    {
        throw "wrong size";
    }

    for (size_t i = 0; i < v.size(); i++)
    {
        if (i != v[i])
        {
            throw "test_push_back failed";
        }
    }
}

void test_update()
{
    ads::vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    for (size_t i = 0; i < v.size(); i++)
    {
        v[i] = i * 2;
    }

    for (size_t i = 0; i < v.size(); i++)
    {
        if (i * 2 != v[i])
        {
            throw "test_update failed";
        }
    }
}

int main()
{
    test_push_front();
    test_push_back();
    test_update();
    _CrtDumpMemoryLeaks();
}
