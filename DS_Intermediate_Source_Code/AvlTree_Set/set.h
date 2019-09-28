#pragma once

#include "avl.h"

template<class T>
class set {
    avl<T> *tree;
public:
    typedef typename avl<T>::iterator_type iterator_type;

    set() {
        tree = new avl<T>();
    }
    
    set(set<T>&& other) : tree(other.tree) {
        other.tree = nullptr;
    }

    ~set() {
        if (tree) {
            delete tree;
        }
    }

    void insert(const T& value) {
        if (!tree->contains(value)) {
            tree->add(value);
        }
    }

    bool remove(const T& val) {
        return tree->remove(val);
    }

    size_t size() const {
        return tree->size();
    }

    bool contains(const T& value) const {
        return tree->contains(value);
    }

    set<T> set_intersection(set<T>& other) {
        set<T> result;

        set<T>* smaller = (this->size() < other.size()) ? this : &other;
        set<T>* larger = (this == smaller) ? &other : this;

        for (auto i : *smaller) {
            if (larger->contains(i)) {
                result.insert(i);
            }
        }

        return std::move(result);
    }

    set<T> set_union(set<T>& other) {
        set<T> result;

        for (auto i : *this) {
            result.insert(i);
        }

        for (auto i : other) {
            result.insert(i);
        }

        return std::move(result);
    }

    set<T> set_difference(set<T>& other) {
        set<T> result;

        for (auto i : *this) {
            if (!other.contains(i)) {
                result.insert(i);
            }
        }

        return std::move(result);
    }

    set<T> set_symmetric_difference(set<T>& other) {
        auto intersection = this->set_intersection(other);

        auto this_diff = this->set_difference(intersection);
        auto other_diff = other.set_difference(intersection);

        auto result = this_diff.set_union(other_diff);
        
        return std::move(result);
    }

    iterator_type begin() {
        return tree->begin();
    }

    iterator_type end() {
        return tree->end();
    }
};