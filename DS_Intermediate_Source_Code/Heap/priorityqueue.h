#pragma once

#include "heap.h"

template<class T, class Compare = std::less<T>>
class priority_queue{
    heap<T, Compare> heap;
public:
    T& top() {
        return heap.top();
    }

    bool empty() {
        return heap.empty();
    }

    size_t size() {
        return heap.count();
    }

    void push(const T& value) {
        heap.push(value);
    }

    void pop() {
        heap.pop();
    }
};