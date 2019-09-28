#include "tbb/tbb.h"

#include <iostream>
#include <thread>

void concurrent_queue_example() {
    tbb::concurrent_queue<int> values;

    auto push_values = [&values](int count) {
        for (int i = 0; i < count; i++) {
            values.push(i);
        }
    };

    std::thread pusher = std::thread(push_values, 10000);

    int temp, popped = 0;
    while (popped < 10000) {
        popped += values.try_pop(temp) ? 1 : 0;
    }

    pusher.join();

    std::cout << "Popped: " << popped 
                << " items" << std::endl;
}


template<class T, class C>
void print_pq(tbb::concurrent_priority_queue<T, C>& queue) {
    int temp;

    while (queue.try_pop(temp)) {
        std::cout << temp << ' ';
    }
    std::cout << std::endl;
}

template<class iter>
void print_array(iter begin, iter end) {
    while (begin != end) {
        std::cout << *begin << ' ';
        begin++;
    }

    std::cout << std::endl;
}

void priority_queue_single_thread_example() {

    // shuffle the values 1..10 randomly
    int values[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::random_shuffle(std::begin(values), std::end(values));

    print_array(std::begin(values), std::end(values));

    tbb::concurrent_priority_queue<int, std::greater<int>> gq;
    tbb::concurrent_priority_queue<int, std::less<int>> lq;

    // add the shuffled values to the priority queues
    for (int i = 0; i < 10; i++) {
        gq.push(values[i]);
        lq.push(values[i]);
    }

    // print the queues in priority order
    print_pq(gq);
    print_pq(lq);
}