#include "tbb\tbb.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void schedule_cancel(tbb::task_group_context& group) {
    std::thread kill_thread([&group](){
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Cancelling task group..." << std::endl;
        group.cancel_group_execution();
    });
    kill_thread.detach();
}

void cancel_parallel_do() {
    tbb::task_group_context group;

    std::vector<int> data(200000);
    int count = 0;
    std::generate(data.begin(), data.end(), [&count]{return count++; });

    schedule_cancel(group);

    tbb::parallel_do(data, [](int value) {
        this_thread::sleep_for(chrono::milliseconds(250));
        cout << value << endl;
    }, group);

    cout << "Cancelled: " << group.is_group_execution_cancelled() << endl;
}