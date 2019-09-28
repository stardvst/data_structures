#include <iostream>
#include <string>
#include <sstream>

#include "blocking_queue.h"

blocking_queue<std::string> queue;

void add(const unsigned int count)
{
    for (unsigned int current = 0; current < count; current++)
    {
        std::stringstream strm;
        strm << std::this_thread::get_id() << " " << current;
        queue.enqueue(strm.str());
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void blocking_queue_test()
{
    const unsigned int iterations = 100;

    std::thread add_thread1(add, iterations);
    std::thread add_thread2(add, iterations);

    for (unsigned int i = 0; i < iterations * 2; )
    {
        std::string value;
        if (queue.try_deque(value, std::chrono::milliseconds(50)))
        {
            std::cout << value << std::endl;
            i++;
        }
        else
        {
            std::cout << "Timed out..." << std::endl;
        }
    }

    add_thread1.join();
    add_thread2.join();
}
