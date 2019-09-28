#include "cache.h"
#include <random>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
using std::string;
using std::stringstream;

namespace cache_test {

    typedef cache<int, std::string, tbb::spin_rw_mutex> cache_t;

    string int_to_string(int value) {
        stringstream ss;
        ss << value;

        return ss.str();
    }

    enum action {
        update_action,
        remove_action,
        read_action,
    };

    void read(cache_t* cache, int value) {
        std::string found;
        if (cache->read(value, found)) {
            std::cout << std::endl << "Key=" << value << "  Value=" << found << std::endl;
        }
        else {
            std::cout << ".";
        }
    }

    void update(cache_t* cache, int value) {
        cache->update(value, int_to_string(value));
    }

    void remove(cache_t* cache, int value) {
        cache->remove(value);
    }

    void cache_test_thread(cache_t* cache, action act) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(1, 100000000);

        for (int i = 0; i < 200000; i++) {
            int next = uni(rng);
            switch (act) {
            case action::read_action:
                read(cache, next);
                break;
            case action::update_action:
                update(cache, next);
                break;
            case action::remove_action:
                remove(cache, next);
                break;
            }
        }
    }


    void cache_test() {
        cache_t cache;

        std::thread threads[] = {
            std::thread(cache_test_thread, &cache, action::read_action),
            std::thread(cache_test_thread, &cache, action::update_action),
            std::thread(cache_test_thread, &cache, action::update_action),
            std::thread(cache_test_thread, &cache, action::remove_action),
            std::thread(cache_test_thread, &cache, action::remove_action),
        };

        for (auto& t : threads) {
            t.join();
        }
    }
}