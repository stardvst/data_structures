#include <future>
#include <thread>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

template<class _Iter>
int parallel_sum(_Iter start, _Iter end)
{
    auto length = std::distance(start, end);
    if (length < 1000)
    {
        return std::accumulate(start, end, 0);
    }

    auto mid = start + length / 2;

    auto left = std::async(std::launch::async, 
                        parallel_sum<_Iter>, mid, end);

    return parallel_sum(start, mid) + left.get();
}

void parallel_sum_test()
{
    const int expected = 100000;

    vector<int> data(expected, 1);

    int result = parallel_sum(data.begin(), data.end());

    cout << ((expected == result) ? "PASSED" : "FAILED") << endl;
}

void background_sum_test();
void packaged_sum_test();
void async_test();
void background_exception_sum_test();

void execute_on_background2()
{
    std::cout << "execute_on_background: " << std::this_thread::get_id() << std::endl;
}

int async_sum(int val1, int val2)
{
    cout << "Executing on thread " << this_thread::get_id() << endl;
    return val1 + val2;
}

void async_test2();

void main()
{
    async_test2();

    cout << "Main thread is " << this_thread::get_id() << endl;

    auto bg_async = std::async(std::launch::async, async_sum, 10, 20);
    auto bg_deferred = std::async(std::launch::deferred, async_sum, 10, 20);
    auto bg_default = std::async(async_sum, 10, 20);

    cout << "Async: " << bg_async.get() << endl;
    cout << "Deferred: " << bg_deferred.get() << endl;
    cout << "Default: " << bg_default.get() << endl;
}