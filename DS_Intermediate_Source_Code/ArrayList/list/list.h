#pragma once

template<class T>
class dlist {
    template<class T>
    struct dlistnode {
        T value;
        dlistnode<T>* prev;
        dlistnode<T>* next;
    };

    size_t count;
    dlistnode<T>* head;
    dlistnode<T>* tail;
public:
    dlist() : count(0), head(nullptr), tail(nullptr) {}

    void push_front(const T& val) {
        dlistnode<T>* node = new dlistnode<T>();
        node->value = val;
        node->next = head;
        node->prev = nullptr;

        if (empty()) {
            head = node;
            tail = node;
        }
        else {
            head->prev = node;
            head = node;
        }

        count++;
    }

    void push_back(const T& val) {
        dlistnode<T>* node = new dlistnode<T>();
        node->value = val;
        node->next = nullptr;
        node->prev = tail;

        if (empty()) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }

        count++;
    }

    T& front() const {
        return head->value;
    }

    T& back() const {
        return tail->value;
    }

    void pop_front() {
        dlistnode<T>* first = head;
        head = head->next;
        delete first;

        count--;

        if (empty()) {
            tail = nullptr;
        }
    }

    void pop_back() {
        dlistnode<T>* last = tail;
        tail->prev->next = null;
        delete last;

        count--;

        if (empty()) {
            head = nullptr;
        }
    }

    size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }
};