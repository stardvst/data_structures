#include <thread>
#include <iostream>
#include <mutex>
#include <string>
#include <queue>

std::mutex output_mutex;

void write_to_console(const int count)
{
    for (int i = 0; i < count; i++)
    {
        std::cout << "Thread " << std::this_thread::get_id()
                  << " write_to_console loop " 
                  << i << " of " << count
                  << std::endl;
    }
}

void write_to_console_linear(const int count)
{
    std::unique_lock<std::mutex> lock(output_mutex);

    for (int i = 0; i < count; i++)
    {
        std::cout << "Thread " << std::this_thread::get_id()
            << " write_to_console loop "
            << i << " of " << count
            << std::endl;
    }
}


void write_to_console_interleaved(const int count)
{
    for (int i = 0; i < count; i++)
    {
        output_mutex.lock();

        std::cout << "Thread " << std::this_thread::get_id()
            << " write_to_console loop "
            << i << " of " << count
            << std::endl;

        output_mutex.unlock();
    }
}

void sync_console_output()
{
    std::thread threads[] =
    {
        std::thread(write_to_console_interleaved, 1000),
        std::thread(write_to_console_interleaved, 1000),
        std::thread(write_to_console_interleaved, 1000),
        std::thread(write_to_console_interleaved, 1000),
        std::thread(write_to_console_interleaved, 1000),
    };

    for (std::thread& t : threads)
    {
        t.join();
    }
}

void run_timed_test();
void recursive_tests();
void once_example();

std::mutex my_mutex;

void recursive_lock_test();
void once_example();

void main()
{
    once_example();
}

