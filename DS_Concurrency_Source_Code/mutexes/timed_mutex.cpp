#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std;

std::timed_mutex shared_lock;

void try_to_take()
{
    unique_lock<timed_mutex> guard(shared_lock);

    if (guard.try_lock_for(chrono::seconds(5)))
    {
        cout << "We locked the mutex!" << endl;
    }
    else
    {
        cout << "We could not lock the mutex" << endl;
    }
}

void try_lock_until_time()
{
    unique_lock<timed_mutex> guard(shared_lock);
    auto until_time = chrono::steady_clock::now() + chrono::seconds(5);

    if (guard.try_lock_until(until_time))
    {
        cout << "We locked the mutex!" << endl;
    }
    else
    {
        cout << "We could not lock the mutex" << endl;
    }
}

void fail_to_take()
{
    lock_guard<timed_mutex> lock(shared_lock);
    thread will_timeout(try_to_take);

    will_timeout.join();
}

void spin_and_wait()
{
    while (true)
    {
        unique_lock<timed_mutex> timed_lock(shared_lock, std::defer_lock);

        if (timed_lock.try_lock_for(chrono::milliseconds(100)))
        {
            cout << this_thread::get_id() << " took lock" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void run_timed_test()
{
    auto func = spin_and_wait;
    std::thread threads[] =
    {
        std::thread(func),
        std::thread(func),
        std::thread(func),
        std::thread(func),
        std::thread(func)
    };

    for (std::thread& t : threads)
    {
        t.join();
    }
}
