#include <iostream>
#include <random>
#include <functional>
#include <cassert>
#include <thread>
#include <chrono>
#include "priorityqueue.h"

enum Priority {
    Idle = 0,
    Normal = 1,
    Urgent = 2,
};

struct Job {
    int jobId;
    Priority priority;

    Job() : jobId(-1), priority(Idle) {}

    Job(int id, Priority pri)
        : jobId(id), priority(pri) {}

    Job(const Job& other)
        : jobId(other.jobId), priority(other.priority) {}

    void process() {
        // perform some work
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<int> distribution(10, 500);

        std::cout << "[" << jobId << "] (" << priority << ") - starting...";
        std::this_thread::sleep_for(std::chrono::milliseconds(distribution(generator)));
        std::cout << "DONE" << std::endl;
    }
};

struct JobOrder {
    bool operator()(const Job& left, const Job& right) {
        return left.priority > right.priority;
    }
};

Priority random_priority() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, 2);

    return static_cast<Priority>(distribution(generator));
}

Job load_job(int id) {
    return Job(id, random_priority());
}

void main2() {
    priority_queue<Job, JobOrder> jobs;
    for (int id = 0; id < 20; id++) {
        jobs.push(load_job(id));
    }

    while (!jobs.empty()) {
        Job job = jobs.top();
        jobs.pop();
        job.process();
    }
}

void main() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);

    // Create a min heap (lesser values first)
    heap<int, std::less<int>> h;

    for (int i = 1000000; i > 0; i--){
        h.push(distribution(generator));
    }

    // while the heap is not empty
    while (!h.empty()) {
        // get the top (least) value
        int current = h.top();

        // print some status
        if ((h.size() % 100000) == 0) {
            std::cout << current << std::endl;
        }

        // remove it from the heap
        h.pop();
    }

    std::cout << "Done!" << std::endl;
}