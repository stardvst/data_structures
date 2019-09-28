#include <mutex>
#include <thread>
#include <iostream>

using namespace std;

void recursive_fails()
{
    mutex non_recursive;
    unique_lock<mutex> nr(non_recursive, std::defer_lock);

    // takes the lock
    nr.lock();

    // fails because non-recursive
    nr.lock();
}

void recursive_still_does_not_work()
{
    recursive_mutex recursive;
    unique_lock<recursive_mutex> rec(recursive, std::defer_lock);

    // takes the lock
    rec.lock();

    // succeeds because recursive
    rec.lock();

    // exception generated during destruction because
    // unbalanced lock/unlock calls
}

int binary_search(const int* values, 
    const int start, 
    const int end, 
    const int toFind, 
    recursive_mutex& lock)
{
    const int NOT_FOUND = -1;
    const int middle = start + ((end - start) / 2);

    lock_guard<recursive_mutex> rl(lock);

    if (start == end)
    {
        return values[start] == toFind ? start : NOT_FOUND;
    }

    if (values[middle] == toFind)
    {
        return middle;
    }

    return toFind < values[middle]
        ? binary_search(values, start, middle, toFind, lock)
        : binary_search(values, middle + 1, end, toFind, lock);
}

void recursive_lock(recursive_mutex &lock, int attempt)
{
    lock_guard<recursive_mutex> guard(lock);
    if (attempt < 10)
    {
        recursive_lock(lock, attempt + 1);
    }
}

void recursive_lock_test()
{
    recursive_mutex m;
    recursive_lock(m, 1);
}


void recursive_tests()
{
    int values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    const int count = sizeof(values) / sizeof(values[0]);

    recursive_mutex lock;

    for (int i = 0; i < count; i++)
    {
        int index = binary_search(values, 0, count - 1, i, lock);

        if (index != i)
        {
            throw exception("failed to find expected value");
        }
    }
}

