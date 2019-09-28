#pragma once

template<class T>
class arraylist {
private:
    size_t _size = 0;
    size_t _head = 0;
    size_t _tail = 0;
    size_t _capacity = 0;
    T* data = nullptr;

    void grow_if_necessary() {

    }

    void add_front(const T& val) {
        
    }
public:
    T& front() {
        return data[_head];
    }

    T& back() {
        return data[_tail];
    }

    void pop_front() {
        remove_front();
    }

    void pop_back() {
        remove_back();
    }

    void push_front(const T& val) {
        add_front(val);
    }

    void push_back(const T& val) {
        add_back(val);
    }

    size_t size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }
};