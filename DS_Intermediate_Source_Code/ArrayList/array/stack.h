#pragma once

#include "deque.h"

template<class T>
class stack {
    deque<T> data;

public:
    bool empty() {
        return data.empty();
    }

    size_t size() {
        return data.size();
    }

    T& top() {
        return data.head();
    }

    void push(const T& val) {
        data.push_front(val);
    }

    void pop() {
        data.pop_front();
    }
};