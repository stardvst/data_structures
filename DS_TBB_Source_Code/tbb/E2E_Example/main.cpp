#include <iostream>
#include <map>
#include "tbb/tbb.h"
#include "ReviewRepository.h"

std::unique_ptr<ReviewRepository> run_serial(int count);
std::unique_ptr<ReviewRepository> run_parallel(int count);


void print_summary(const std::unique_ptr<ReviewRepository>& repository) {

    std::map<int, int> hist;
    repository->hist(hist);
    for (int i = 1; i < 6; i++) {
        std::cout << i << ": " << hist[i] << std::endl;
    }

    std::cout << "Average: " << repository->avg() << std::endl;

    std::cout << "Top 5 Sentiment Scores:" << std::endl;
    repository->top(5, [](const Review& review) {
        std::cout << review.reviewer.Name << ": "
                  << review.review.Sentiment << std::endl;
    });

    std::cout << std::endl;
}

tbb::tick_count::interval_t test_serial(const int limit) {
    auto start = tbb::tick_count::now();

    std::unique_ptr<ReviewRepository> repository = run_serial(limit);
    print_summary(repository);

    return tbb::tick_count::now() - start;
}

tbb::tick_count::interval_t test_parallel(const int limit) {
    auto start = tbb::tick_count::now();
    auto parallel = run_parallel(limit);

    print_summary(parallel);

    return tbb::tick_count::now() - start;

}

int main() {
    const int limit = 2000;

    std::cout << "Starting Serial..." << std::endl;
    auto serial_time = test_serial(limit);

    std::cout << "Starting Parallel..." << std::endl;
    auto parallel_time = test_parallel(limit);

    std::cout << "Serial time: " << serial_time.seconds() << std::endl;
    std::cout << "Parallel time: " << parallel_time.seconds() << std::endl;
    std::cout << "Difference: " << serial_time.seconds() / parallel_time.seconds() << std::endl;

}





























