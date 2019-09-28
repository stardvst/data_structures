#include <thread>
#include <iostream>

using namespace std;

void basic_writer();
void thread_function(int count);

void create_thread()
{
    thread empty = thread();
    empty.get_id();
}

void thread_function(int count)
{
    for (int iter = 0; iter < count; iter++)
    {
        cout << "Child Thread!" 
             << iter << " of " << count << endl;
    }
}

void spawn_writer()
{
    thread child = thread(basic_writer);
    child.join();
}

void spawn_writers(int count)
{
    thread** threads = new thread*[count];

    // create the threads
    for (int i = 0; i < count; i++)
    {
        threads[i] = new thread(basic_writer);
    }

    // wait for each one to complete
    for (int i = 0; i < count; i++)
    {
        threads[i]->join();
    }
}

void basic_writer()
{
    int limit = 100;

    for (int iter = 0; iter < limit; iter++)
    {
        cout << this_thread::get_id() << " writer thread iteration "
             << iter << " of " << limit << endl;
    }
}