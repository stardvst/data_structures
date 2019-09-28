#include <future>
#include <thread>
#include <numeric>
#include <iostream>
#include <vector>

template<class _Ret>
class task
{
    typedef std::function<_Ret()> Func;

    Func _func;
    std::promise<_Ret> _promise;
    std::future<_Ret> _future;

    static void execute_on_background(Func func, std::promise<_Ret>& promise)
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

public:
    task(Func func)
    {
        _func = func;
        _future = _promise.get_future();
    }

    std::future<_Ret> get_future()
    {
        return std::move(_future);
    }

    void operator()()
    {
        std::thread background(execute_on_background, _func, std::move(_promise));
        background.detach();
    }
};

int expensive_operation(int iterations)
{
    std::cout << "Expensive Operation on thread: " << std::this_thread::get_id() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::vector<int> data(iterations, 1);

    return std::accumulate(data.begin(), data.end(), 0);
}

void run_task(task<int>& my_task)
{
    my_task();
}

void packaged_sum_test()
{
    const int iterations = 1000000;

    task<int> background_sum(std::bind(expensive_operation, iterations));

    std::future<int> result = background_sum.get_future();

    run_task(background_sum);

    std::cout << "Waiting on expensive operation to finish..." << std::endl;

    int actual = result.get();

    std::cout << "Completed" << std::endl;

    std::cout << ((iterations == actual) ? "PASSED" : "FAILED") << std::endl;
}