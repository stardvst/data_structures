#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

mutex console_lock;
void report(const string& message)
{
    lock_guard<mutex> guard(console_lock);
    cout << this_thread::get_id() << " " << message << endl;
}

condition_variable all_ready;
mutex all_ready_mutex;

atomic<bool> all_ready_flag = false;

void wait_for_all()
{
    report("started");

    unique_lock<mutex> lk(all_ready_mutex);
    all_ready.wait(lk, []
    {
        report("wake up");
        return all_ready_flag == true; 
    });

    report("finished");

}

void report_and_notify()
{
    report("creating threads");

    thread t1(wait_for_all);
    thread t2(wait_for_all);
    thread t3(wait_for_all);

    report("setting flag");

    all_ready_flag = true;

    this_thread::sleep_for(chrono::seconds(5));

    report("notifying");

    all_ready.notify_all();

    t1.join();
    t2.join();
    t3.join();
}

condition_variable step_done;
string status;
bool done = false;

void execute_steps()
{
    for (int i = 0; i < 10; i++)
    {
        stringstream strm;

        strm << "step " << i << " done";
        this_thread::sleep_for(chrono::seconds(1));
        status = strm.str();

        step_done.notify_one();
    }

    status = "done";
    done = false;

    step_done.notify_one();
}

void test_loop()
{
    mutex cv_mutex;
    unique_lock<mutex> cv_lock(cv_mutex);

    thread steps(execute_steps);

    while (!done)
    {
        step_done.wait(cv_lock, []{return !done; });
        cout << status << endl;
    }

    steps.join();
}


class event_waiter
{
    atomic<bool> notified;

public:
    event_waiter() : notified(false) {}
    event_waiter(const event_waiter&) = delete;

    void notify()
    {
        notified = true;
    }

    void wait()
    {
        while (!notified)
        {
            this_thread::yield();
        }
    }
};

class event_waiter_spurious
{
    atomic<bool> notified;

public:
    event_waiter_spurious() : notified(false) {}
    event_waiter_spurious(const event_waiter&) = delete;

    void notify()
    {
        notified = true;
    }

    template<class Predicate>
    void wait(Predicate& done_waiting)
    {
        while (!done_waiting() && !notified)
        {
            this_thread::yield();
        }
    }
};

class event_waiter_spurious_mutex
{
    atomic<bool> notified;

public:
    event_waiter_spurious_mutex() : notified(false) {}
    event_waiter_spurious_mutex(const event_waiter&) = delete;

    void notify()
    {
        notified = true;
    }

    template<class Predicate>
    void wait(unique_lock<mutex>& lock, Predicate& done_waiting)
    {
        while (!done_waiting() && !notified)
        {
            lock.unlock();
            this_thread::yield();
            lock.lock();
        }
    }
};

void network_test();
void network_test_non();
void pinger();
void blocking_queue_test();

int main()
{
    blocking_queue_test();
}

int main2()
{
    event_waiter_spurious_mutex cvar;
    bool done = false;
    mutex mtx;

    thread wait([&mtx, &done, &cvar]
    {
        unique_lock<mutex> child_thread_lock(mtx);

        cout << "working" << endl;
        this_thread::sleep_for(chrono::seconds(5)); 

        cout << "notifying" << endl;

        done = true;
        cvar.notify();
    });

    unique_lock<mutex> lock(mtx);

    cout << "waiting" << endl;
    cvar.wait(lock, [&done]{ return done; });

    cout << "done" << endl;
    wait.join();

    return 0;
}