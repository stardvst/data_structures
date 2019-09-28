#pragma once

#include "deque.h"

template<class T>
class queue {
private:
    deque<T> data;

public:
    void enque(const T& val) {
        data.push_back(val);
    }

    void deque() {
        data.pop_front();
    }

    T& front() {
        return data.front();
    }

    size_t size() {
        return data.size();
    }

    bool empty() {
        return data.empty();
    }
};