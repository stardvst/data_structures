#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <iostream>

using namespace std;

recursive_mutex console_lock;
mutex complete_mutex;

class tracing
{
public:
    tracing()
    {
        unique_lock<recursive_mutex> con(console_lock);
        cout << this_thread::get_id() << " tracing::tracing()" << endl;
    }

    ~tracing()
    {
        unique_lock<recursive_mutex> con(console_lock);
        cout << this_thread::get_id() << " tracing::~tracing()" << endl;
    }

    void func()
    {
        unique_lock<recursive_mutex> con(console_lock);
        cout << this_thread::get_id() << " tracing::func()" << endl;
    }
};

#if C11
thread_local
#endif
tracing thread_local_tracing;

condition_variable cv_tl;
atomic<bool> _done = false;

void use_thread_local()
{
    unique_lock<mutex> cv_lock(complete_mutex);
    thread_local_tracing.func();

    _done = true;
    notify_all_at_thread_exit(cv_tl, std::move(cv_lock));
}

void thread_local_test()
{
    unique_lock<mutex> cv_lock(complete_mutex);

    thread t1(use_thread_local);

    while (!_done)
    {
        cv_tl.wait(cv_lock);
    }

    cout << "Threads done" << endl;
}