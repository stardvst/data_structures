#include "tbb/tbb.h"
#include <thread>
#include <string>
#include <iostream>

void add_values_in_loop(tbb::concurrent_hash_map<std::string, int>* map, int min, int max) {
    for (int i = min; i < max; i++){
        tbb::concurrent_hash_map<std::string, int>::accessor ac;
        std::string key = std::to_string(i);
        if (map->insert(ac, key)) {
            ac->second = i;
        }
    }
};

void add_values(tbb::concurrent_hash_map<std::string, int>* map, int min, int max) {
    tbb::concurrent_hash_map<std::string, int>::accessor ac;

    for (int i = min; i < max; i++){
        std::string key = std::to_string(i);
        while (true) {
            if (map->insert(ac, key)) {
                ac->second = i;
                ac.release();
                break;
            }
        }
    }
};

void find_values(tbb::concurrent_hash_map<std::string, int>* map, int min, int max) {
    for (int i = min; i < max; i++) {
        tbb::concurrent_hash_map<std::string, int>::const_accessor ac;
        std::string key = std::to_string(i);

        bool found = map->find(ac, key);
        ac.release();

        if (found) {
            std::cout << key << " found" << std::endl;
        }
        else {
            std::cout << key << " NOT found" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
};


void hash_map_basic_insert() {
    tbb::concurrent_hash_map<std::string, int> map;

    std::thread insert_threads[] = {
        std::thread(add_values, &map, 1, 100000),
        std::thread(add_values, &map, 100001, 200000),
        std::thread(add_values, &map, 200001, 300000),
        std::thread(add_values, &map, 300001, 400000),
    };

    std::thread find_threads[] = {
        std::thread(find_values, &map, 1, 1000),
        std::thread(find_values, &map, 100000, 101000),
        std::thread(find_values, &map, 1000000, 1001000),
    };

    for (std::thread& t : insert_threads) t.join();
    for (std::thread& t : find_threads) t.join();
}