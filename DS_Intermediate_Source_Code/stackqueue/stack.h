#pragma once

#include "deque.h"

template<class T>
class stack {
    deque<T> data;

public:
    void push(const T& val) {
        data.push_front(val);
    }

    void pop() {
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