#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void linear_execution()
{
    int x = 10;

    cout << x << endl;

    x *= 2;

    cout << x;
}

void thread_function(int id)
{
    for (int i = 1; i <= 500; i++)
    {
        cout << "THREAD " << id << " " << i << endl;
    }
}


int main()
{
    const int COUNT = 1;

    thread threads[COUNT];
    for (int i = 0; i < COUNT; i++)
    {
        threads[i] = thread(thread_function, i);
    }

    for (int i = 0; i < COUNT; i++)
    {
        threads[i].join();
    }

    int i;
    cin >> i;
}