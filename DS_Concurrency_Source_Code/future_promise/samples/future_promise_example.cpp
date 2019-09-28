#include <future>
#include <thread>
#include <numeric>
#include <iostream>
#include <vector>

template<class _Iter, class _Val>
void background_sum_impl(_Iter start, _Iter end, std::promise<_Val>& promise)
{
    try
    {
        promise.set_value(std::accumulate(start, end, 0));
    }
    catch (...)
    {
        promise.set_exception(std::current_exception());
    }
}

template<class _Iter>
std::future<int> background_sum(_Iter start, _Iter end)
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    std::thread background(background_sum_impl<_Iter, int>, 
        start, end, std::move(promise));

    background.detach();

    return std::move(future);
}

void background_sum_test()
{
    std::vector<int> data(100000, 1);
    std::future<int> result = background_sum(data.begin(), data.end());

    result.wait();

    std::cout << ((100000 == result.get()) ? "PASSED" : "FAILED") << std::endl;
}
