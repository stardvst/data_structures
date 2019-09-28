#include <iostream>
#include <thread>
#include <atomic>
using std::cout;
using std::endl;
using std::hex;
using std::thread;

static std::atomic<__int64> atomic = 0;

void print_function()
{
    while (true)
    {
        cout << hex << atomic << endl;
    }
}

void update_function()
{
    while (true)
    {
        atomic = ~atomic;
    }
}

int main(int argc, const char **argv)
{
    auto update = thread(update_function);
    auto print = thread(print_function);

    update.join();
    print.join();

    return 0;
}