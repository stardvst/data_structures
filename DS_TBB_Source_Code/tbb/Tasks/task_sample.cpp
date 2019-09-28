#include "tbb\tbb.h"
#include <iostream>

class CountDown : public tbb::task {
private:
    int _count;

    CountDown& create_countdown(int count) {
        return *new(task::allocate_child()) CountDown(count);
    }
    
public:
    CountDown(int count) : _count(count) {}

    task* execute() {
        std::cout << _count << std::endl;

        if (_count > 1) {
            set_ref_count(3);

            spawn(create_countdown(_count - 1));
            spawn(create_countdown(_count - 2));

            wait_for_all();
        }

        return nullptr;
    }
};


void count_down(int count) {
    std::cout << "Count: " << count << std::endl;
    if (count > 1) {
        count_down(count - 1);
        count_down(count - 2);
    }
}

void task_sample() {
    CountDown& root = *new(tbb::task::allocate_root()) CountDown(4);
    tbb::task::spawn_root_and_wait(root);
}