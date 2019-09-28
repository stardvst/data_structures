#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <vector>

using std::string;
using std::stringstream;
using std::thread;
using std::vector;
using std::mutex;
using std::lock_guard;
using std::cout;
using std::endl;

static vector<string> shared;
static mutex shared_mutex;

void use_shared()
{
    for (int i = 0; i < 100; i++)
    {
        stringstream sstm;

        // [37627] 1 calls
        sstm << "[" << std::this_thread::get_id() << "] " << i << " calls";

        lock_guard<mutex> lock(shared_mutex);
        shared.push_back(sstm.str());
    }
}

void main()
{
    thread t1 = thread(use_shared);
    thread t2 = thread(use_shared);

    t1.join();
    t2.join();

    for (string output : shared)
    {
        cout << output << endl;
    }
}