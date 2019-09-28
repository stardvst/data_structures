#pragma once

#include "deque.h"

template<class T>
class queue {
    deque<T> data;

public:
    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

    T front() {
        return data.front();
    }

    void push(const T& val) {
        return data.push_back(val);
    }

    void pop() {
        return data.pop_front();
    }
};