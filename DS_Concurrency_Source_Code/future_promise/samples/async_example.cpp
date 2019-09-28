#include <thread>
#include <future>
#include <iostream>
#include <vector>
#include <numeric>

template<class _Ret>
void execute_on_background(std::promise<_Ret>& promise, 
                           std::function<_Ret()>& func)
{
    try
    {
        promise.set_value(func());
    }
    catch (...)
    {
        promise.set_exception(std::current_exception());
    }
}

template<class _Ret>
std::future<_Ret> execute_async(std::function<_Ret()>& func)
{
    std::packaged_task<_Ret()> task(func);
    std::future<_Ret> future = task.get_future();

    std::thread background(std::move(task));
    background.detach();

    return std::move(future);
}

int expensive_operation2()
{
    std::cout << "Expensive Operation on thread: " << std::this_thread::get_id() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::vector<int> data(1000000, 1);

    return std::accumulate(data.begin(), data.end(), 0);
}

void bg()
{

}

void async_test2()
{
    std::future<int> result = execute_async<int>(std::function<int()>(expensive_operation2));
    std::future<void> result2 = std::async(bg);
    int iters = result.get();

    std::cout << ((1000000 == iters) ? "PASSED" : "FAILED") << std::endl;
}

int background_sum(int val1, int val2)
{
    return val1 + val2;
}



void sum_with_packaged_task()
{

}


