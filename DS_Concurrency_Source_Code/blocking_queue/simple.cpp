#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <atomic>

using namespace std;

condition_variable ping;
mutex ping_mutex;
bool ping_sent = false;

void start_after_ping()
{
    unique_lock<mutex> lock(ping_mutex);
    ping.wait(lock, []{return ping_sent; });

    cout << "ping received" << endl;
}

void pinger()
{
    unique_lock<mutex> lock(ping_mutex);
    thread wait_thread(start_after_ping);

    ping_sent = true;

    lock.unlock();
    ping.notify_one();

    wait_thread.join();
}
