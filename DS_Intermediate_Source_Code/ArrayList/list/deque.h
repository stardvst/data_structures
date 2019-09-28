#pragma once

#include "list.h"

template<class T>
class deque {
    // doubly linked list
    dlist<T> container;

public:
    // add item to the front of the queue
    void push_front(const T& val) {
        container.push_front(val);
    }

    // add item to the back of the queue
    void push_back(const T& val) {
        container.push_back(val);
    }

    // remove item from the front of the queue
    void pop_front() {
        container.pop_front();
    }

    // remove item from the back of the queue
    void pop_back() {
        container.pop_back();
    }

    // retrieve the front item in the queue
    T front() {
        return container.front();
    }

    // retrieve the back item in the queue
    T back() {
        return container.back();
    }

    // True if the queue is empty, false otherwise
    bool empty() const {
        return container.empty();
    }

    // the number of enqueued items
    size_t size() const {
        return container.size();
    }
};