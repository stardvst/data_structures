#include <thread>
#include <iostream>
#include <mutex>
#include <string>
#include <fstream>

using namespace std;

struct initialize_state
{
    mutex lock;
    bool done;
};

template<class callback>
void initialize(initialize_state& state, callback &&init)
{
    if (!state.done)
    {
        state.lock.lock();
        if (!state.done)
        {
            init();
            state.done = true;
        }
    }
}

initialize_state init_flag;
ofstream logfile;

void open_logfile()
{
    logfile.open("logfile.txt");
}

void log(const string& message)
{
    initialize(init_flag, open_logfile);
    logfile << message << endl;
}


namespace bar
{
ofstream logfile;
mutex initialization_lock;

void open_logfile()
{
    if (!logfile.is_open())
    {
        lock_guard<mutex> guard(initialization_lock);
        if (!logfile.is_open())
        {
            logfile.open("logfile.txt");
        }
    }
}

void log(const string& message)
{
    open_logfile();
    logfile << message << endl;
}


}

void once_example()
{
    log("message 1");
    log("message 2");
    log("message 3");
}