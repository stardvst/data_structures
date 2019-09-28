#include "tbb\tbb.h"
#include <iostream>

class nop_task : public tbb::task {
public:
    task* execute() {
        std::cout << "Executing!" << std::endl;
        return nullptr;
    }
};

void task_do_nothing() {
    nop_task& nop = *new(tbb::task::allocate_root()) nop_task();
    tbb::task::spawn_root_and_wait(nop);
}

class blocking_repeater : public tbb::task {
private:
    int _count;
public:
    blocking_repeater(int count) : _count(count) {}

    task* execute() {
        if (_count > 0) {
            std::cout << "remaining: " << _count << std::endl;

            // allocate the child
            blocking_repeater& child = *new(allocate_child()) blocking_repeater(_count - 1);

            // One for this task and one for the child
            set_ref_count(2);

            // start child and wait
            spawn_and_wait_for_all(child);
        }

        return nullptr;
    }
};

void task_blocking_repeater() {
    blocking_repeater& t = *new(tbb::task::allocate_root()) blocking_repeater(10);
    tbb::task::spawn_root_and_wait(t);
}

class reuse_continuation_repeater : public tbb::task {
private:
    int _count;
public:
    reuse_continuation_repeater(int count) : _count(count) {}

    task* execute() {
        if (_count > 0) {
            std::cout << "remaining: " << _count << std::endl;

            tbb::empty_task& c = *new(allocate_continuation()) tbb::empty_task();
            c.set_ref_count(1);

            recycle_as_child_of(c);

            _count--;

            return this;
        }

        return nullptr;
    }
};

void task_reuse_continuation_repeater() {
    reuse_continuation_repeater& t = *new(tbb::task::allocate_root()) reuse_continuation_repeater(10);
    tbb::task::spawn_root_and_wait(t);
}

