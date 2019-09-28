#include <future>
#include <thread>
#include <numeric>
#include <iostream>
#include <vector>

template<class _Iter, class _Val>
void background_sum_exception_impl(_Iter start, _Iter end, std::promise<_Val>& promise)
{
    try
    {
        throw std::logic_error("logic error during summation");
        promise.set_value(std::accumulate(start, end, 0));
    }
    catch (...)
    {
        promise.set_exception(std::current_exception());
    }
}

template<class _Iter>
std::future<int> background_exception_sum(_Iter start, _Iter end)
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    std::thread background(background_sum_exception_impl<_Iter, int>,
        start, end, std::move(promise));

    background.detach();

    return std::move(future);
}

void background_exception_sum_test()
{
    std::vector<int> data(100000, 1);
    std::future<int> result = background_exception_sum(data.begin(), data.end());

    std::exception_ptr expt;

    try
    {
        int iters = result.get();
        std::cout << "Failure - expected exception" << std::endl;
    }
    catch (...)
    {
        expt = std::current_exception();
    }

    if (expt)
    {
        try
        {
            std::rethrow_exception(expt);
        }
        catch (const std::exception& ex)
        {
            std::cout << "Success!  Caught Exception - " << ex.what() << std::endl;
        }
    }
}