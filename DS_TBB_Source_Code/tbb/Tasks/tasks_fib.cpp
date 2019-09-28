#include "tbb\tbb.h"
#include <iostream>
#include <thread>
#include <chrono>

class FibTask : public tbb::task {
private:
    const long CutOff = 16;
    const long n;
    long* const sum;

    long SerialFib(long n) {

        if (n < 2) {
            return n;
        }
        else {
            return SerialFib(n - 1) + SerialFib(n - 2);
        }
    }

public:
    FibTask(long n_, long* sum_) :
        n(n_), sum(sum_)
    {
    }

    // Overrides virtual function task::execute
    tbb::task* execute() {      
        if (n<CutOff) {
            *sum = SerialFib(n);
        }
        else {
            long x, y;
            FibTask& a = *new(allocate_child()) FibTask(n - 1, &x);
            FibTask& b = *new(allocate_child()) FibTask(n - 2, &y);
            // Set ref_count to "two children plus one for the wait".
            set_ref_count(3);
            // Start b running.
            spawn(b);
            // Start a running and wait for all children (a and b).
            spawn_and_wait_for_all(a);
            // Do the sum
            *sum = x + y;
        }
        return NULL;
    }
};

void tasks_basic()
{
    long sum;
    long n = 38;

    FibTask& a = *new(tbb::task::allocate_root()) FibTask(n, &sum);
    tbb::task::spawn_root_and_wait(a);

    std::cout << sum << std::endl;
}