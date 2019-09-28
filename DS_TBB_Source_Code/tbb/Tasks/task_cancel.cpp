#include "tbb\tbb.h"
#include <iostream>
#include <chrono>
#include <thread>

class infinite_task : public tbb::task {
public:
    tbb::task* execute() {
        while (true) {
            std::cout << "running..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        return nullptr;
    }
};

class cancellable_infinite_task : public tbb::task {
public:
    tbb::task* execute() {
        while (!is_cancelled()) {
            std::cout << "running..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        return nullptr;
    }
};

void schedule_cancel(tbb::task_group_context& group, int seconds) {
    std::thread kill_thread([&group, seconds](){
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        std::cout << "Cancelling task group..." << std::endl;
        group.cancel_group_execution();
    });
    kill_thread.detach();
}

void run_infinite_task() {
    tbb::task_group_context group;
    auto& root = *new(tbb::task::allocate_root(group)) cancellable_infinite_task();

    schedule_cancel(group, 3);

    tbb::task::spawn_root_and_wait(root);
    std::cout << "Task completed..." << std::endl;
}