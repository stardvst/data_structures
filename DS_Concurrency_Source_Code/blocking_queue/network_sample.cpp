#include <iostream>
#include <string>
#include <sstream>
#include <thread>

#include "blocking_queue.h"

using namespace std;

blocking_queue<string> network_queue;

string read_from_network()
{
    return "string";
}

void process_data(string data)
{
    cout << data << endl;
}

void read()
{
    while (true)
    {
        string data = read_from_network();
        network_queue.enqueue(data);
    }
}

void process()
{
    while (true)
    {
        string data;
        network_queue.deque(data);

        process_data(data);
    }
}


// simulates reading data from a network
void network_read_thread()
{
    unsigned count = 0;

    while (true)
    {
        stringstream strm;
        strm << "string " << count++ << " from thread " << this_thread::get_id();

        network_queue.enqueue(strm.str());

        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void network_process_thread()
{
    while (true)
    {
        string value;
        network_queue.deque(value);

        cout << "[" << this_thread::get_id() << "] Processed: " << value << endl;
    }
}

void network_test()
{
    thread data_source(network_read_thread);
    thread data_processor(network_process_thread);

    data_source.join();
    data_processor.join();
}