#pragma once

#include <list>
using std::list;

template<class T>
class stack {
    list<T> data;

public:
    bool empty() {
        return data.empty();
    }

    size_t size() {
        return data.size();
    }

    T& top() {
        return data.back();
    }

    const T& top() const {
        return data.back();
    }

    void push(const T& val) {
        return data.push_back(val);
    }

    void pop() {
        return data.pop_back();
    }
};
