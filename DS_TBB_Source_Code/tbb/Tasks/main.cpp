#include "examples.h"
#include <cstdlib>
#include <time.h>

void run_all()
{
    // tasks_basic();
    task_group_basic();
    // task_do_nothing();
    // task_blocking_repeater();
    // task_reuse_continuation_repeater();
    // partitioned_sum();
    // task_sample();

    // do_example();
    // run_infinite_task();
    // cancel_parallel_do();
}

int main()
{
    srand(time(NULL));
    run_all();
}