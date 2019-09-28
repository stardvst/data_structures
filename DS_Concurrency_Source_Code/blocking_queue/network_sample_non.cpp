#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <queue>
#include <mutex>

using namespace std;

queue<string> network_queue;
mutex network_queue_mutex;

// simulates reading data from a network
void network_read_thread_non()
{
    unsigned count = 0;

    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(500));

        stringstream strm;
        strm << "Packet " << count++ << " from thread " << this_thread::get_id();

        unique_lock<mutex> network_lock(network_queue_mutex);
        network_queue.push(strm.str());
    }
}

void network_process_thread_non()
{
    while (true)
    {
        unique_lock<mutex> network_lock(network_queue_mutex);
        if (network_queue.empty())
        {
            network_lock.unlock();
            this_thread::yield();
            continue;
        }

        string value = network_queue.front();
        network_queue.pop();
        cout << "[" << this_thread::get_id() << "] Processed: " << value << endl;
    }
}

void network_test_non()
{
    thread data_source1(network_read_thread_non);
    thread data_source2(network_read_thread_non);

    thread data_processor1(network_process_thread_non);
    thread data_processor2(network_process_thread_non);

    data_source1.join();
    data_source2.join();
    data_processor1.join();
    data_processor2.join();
}