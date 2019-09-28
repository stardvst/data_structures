#pragma once

template<class T>
class queue {
    template<class T>
    struct queuenode {
        T value;
        queuenode<T>* prev;
        queuenode<T>* next;
    };

    queuenode<T> *head;
    queuenode<T> *back;
    size_t count;

public:
    queue() : head(nullptr), back(nullptr), count(0) {
    }

    bool empty() const {
        return count == 0;
    }

    size_t size() const {
        return count;
    }

    T front() {
        return head->value;
    }

    void push(const T& val) {
        queuenode<T> *node = new queuenode<T>();
        node->next = nullptr;
        node->prev = back;
        node->value = val;

        if (head == nullptr) {
            head = node;
        }
        else {
            back->next = node;
        }

        back = node;
        count++;
    }

    void pop() {
        queuenode<T> *temp = head;
        head = head->next;
        delete temp;
        
        count--;
        
        if (count == 0) {
            head = nullptr;
            back = nullptr;
        }
    }
};