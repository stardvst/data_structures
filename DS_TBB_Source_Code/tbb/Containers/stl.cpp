#include <vector>
#include <thread>
#include <mutex>

void stl_concurrency_problem() {

    std::vector<int> values;

    auto add_values = [&](int min, int max) {
        for (int i = min; i < max; i++) {
            values.push_back(i);
        }
    };

    std::thread threads[] = {
        std::thread(add_values, 1, 100000),
        std::thread(add_values, 100001, 200000)
    };

    for (std::thread& t : threads) {
        t.join();
    }
}


void stl_concurrency_solution() {

    std::vector<int> values;
    std::mutex values_mutex;

    auto add_values = [&](int min, int max) {
        for (int i = min; i < max; i++) {
            std::lock_guard<std::mutex> lock(values_mutex);
            values.push_back(i);
        }
    };

    std::thread threads[] = {
        std::thread(add_values, 1, 100000),
        std::thread(add_values, 100001, 200000)
    };

    for (std::thread& t : threads) {
        t.join();
    }

}
