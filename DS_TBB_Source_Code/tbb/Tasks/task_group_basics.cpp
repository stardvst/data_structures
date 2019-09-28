#include "tbb\tbb.h"
#include <iostream>
#include <thread>
#include <chrono>

void Task(tbb::task_group& group, int taskId) {
    std::this_thread::sleep_for(std::chrono::milliseconds(taskId));
    std::cout << "Task " << taskId << " starting" << std::endl;
    int ms = taskId * 100;
    for (int i = 0; i < 10; i++) {
        if (group.is_canceling()) {
            std::cout << "Task " << taskId << " cancelled" << std::endl;
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    std::cout << "Task " << taskId << " done" << std::endl;
}

void task_group_basic() {
    tbb::task_group group;

    group.run([&group]() { Task(group, 1); });
    group.run([&group]() { Task(group, 2); });
    group.run([&group]() { Task(group, 3); });

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    group.cancel();

    std::cout << "group complete" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}