#pragma once

template<class T>
class stack {
    
    template<class T>
    struct stacknode {
        T value;
        stacknode<T>* next;
    };

    stacknode<T> *head;
    size_t count;

public:
    stack() : head(nullptr), count(0) {}

    bool empty() {
        return count == 0;
    }

    size_t size() {
        return count;
    }

    T& top() {
        return head->value;
    }

    const T& top() const {
        return head->value;
    }

    void push(const T& val) {
        stacknode<T> *node = new stacknode<T>();
        node->next = head;
        node->value = val;
        head = node;
        count++;
    }

    void pop() {
        stacknode<T> *node = head;
        head = node->next;
        delete node;
        count--;
    }
};