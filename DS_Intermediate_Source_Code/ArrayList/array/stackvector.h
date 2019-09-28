#pragma once

#include <vector>
using std::vector;

template<class T>
class stack {
    std::vector<T> data;
public:
    stack() {}

    bool empty() {
        return data.empty();
    }

    size_t size() {
        return data.size();
    }

    T& top() {
        return data[size() - 1];
    }

    const T& top() const {
        return data[size() - 1];
    }

    void push(const T& val) {
        data.push_back(val);
    }

    void pop() {
        data.pop_back();
    }
};