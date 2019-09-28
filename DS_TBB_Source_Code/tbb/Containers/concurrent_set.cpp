#include "tbb/tbb.h"
#include <thread>
#include <string>
#include <iostream>

void add_values(tbb::concurrent_unordered_set<int>* set, int min, int max) {
    for (int i = min; i < max; i++) {
        set->insert(i);
    }
}

void find_values(tbb::concurrent_unordered_set<int>* set, int min, int max) {
    for (int i = min; i < max; i++) {
        tbb::concurrent_unordered_set<int>::iterator found;
        found = set->find(i);

        if (found != set->end()) {
            std::cout << "Found " << i << std::endl;
        }
        else {
            std::cout << "NOT Found " << i << std::endl;
        }
    }
}

void remove_all(tbb::concurrent_unordered_set<int>* set) {
    // prefer:  set->clear();

    while (!set->empty()) {
        set->unsafe_erase(set->begin());
    }
}

void unordered_set_basic_operations() {
    tbb::concurrent_unordered_set<int> set;

    std::thread insert_threads[] = {
        std::thread(add_values, &set, 1, 100000),
        std::thread(add_values, &set, 100001, 200000),
    };

    std::thread find_threads[] = {
        std::thread(find_values, &set, 1, 1000),
        std::thread(find_values, &set, 100000, 101000),
    };

    for (std::thread& t : insert_threads) t.join();
    for (std::thread& t : find_threads) t.join();

    remove_all(&set);
}