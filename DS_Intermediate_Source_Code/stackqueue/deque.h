#pragma once
#include <list>

using std::list;

template<class T>
class deque {
    list<T> data;
    
public:
    T& front() {
        return data.front();
    }

    T& back() {
        return data.back();
    }

    void pop_front() {
        data.pop_front();
    }

    void pop_back() {
        data.pop_back();
    }

    void push_front(const T& val) {
        data.push_front(val);
    }

    void push_back(const T& val) {
        data.push_back(val);
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};