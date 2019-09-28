#include <iostream>
#include <thread>
#include <atomic>

using std::cout;
using std::endl;
using std::thread;
using std::atomic;
using std::memory_order;

static atomic<int> x;

void loop_until_changed()
{
    while (0 == x.load(memory_order::memory_order_seq_cst))
    {
        cout << "looping..." << endl;
    }
}

void change()
{
    while (true)
    {
        x.store(
            ~x.load(memory_order::memory_order_seq_cst), 
            memory_order::memory_order_seq_cst);
    }
}

void main()
{
    auto t1 = thread(loop_until_changed);
    auto t2 = thread(change);

    t2.join();
    t1.join();
}