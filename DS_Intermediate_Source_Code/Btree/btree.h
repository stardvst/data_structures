#pragma once

#include <list>
#include <algorithm>

using std::list;
using std::lower_bound;

template<class T>
struct btreenode {
    typedef btreenode<T>* node_ptr;

    list<T> values;
    list<node_ptr> children;
    node_ptr parent;
    const size_t minDegree;

    btreenode(int minimumDegree)
        : parent(nullptr), minDegree(minimumDegree)
    {
    }

    btreenode(node_ptr parentNode, int minimumDegree) 
        : parent(parentNode), minDegree(minimumDegree)
    { 
    }

    template<class ValueIterator>
    btreenode(node_ptr parentNode, int minimumDegree,
        ValueIterator& values_begin, ValueIterator& values_end)
        : parent(parentNode), minDegree(minimumDegree)  {
        values.insert(values.begin(), values_begin, values_end);
    }


    template<class ValueIterator, class ChildIterator>
    btreenode(node_ptr parentNode, int minimumDegree,
        ValueIterator& values_begin, ValueIterator& values_end,
        ChildIterator& child_begin, ChildIterator& child_end)
        : parent(parentNode), minDegree(minimumDegree)  {
        values.insert(values.begin(), values_begin, values_end);
        children.insert(children.begin(), child_begin, child_end);
    }

    bool full() {
        return values.size() >= (2 * minDegree - 1);
    }

    bool leaf(){
        return children.size() == 0;
    }

    void splitChild(int childIndex) {
        // Splits a child node by pulling the middle node up from it
        // into the current (parent) node.

        //     [3          9]
        // [1 2] [4 5 6 7 8] [10 11] 
        //
        // splitting [4 5 6 7 8] would pull 6 up to its parent
        //
        //     [3     6     9]
        // [1 2] [4 5] [7 8] [10 11] 

        // the child we're splitting
        node_ptr child = *std::next(children.begin(), childIndex);

        // the child value index we'll split at
        int medianIndex = child->values.size() / 2;

        // the index in the child we're splitting at
        list<T>::iterator childMedianIter = std::next(child->values.begin(), medianIndex);

        // the value we're pulling up
        T valueToPullup = *childMedianIter;

        node_ptr newLeft, newRight;

        if (child->children.size() > 0) {
            // build [4, 5]
            newLeft = new btreenode<T>(this, minDegree,
                child->values.begin(), std::next(child->values.begin(), medianIndex),
                child->children.begin(), std::next(child->children.begin(), medianIndex + 1));

            // child [7, 8]
            newRight = new btreenode<T>(this, minDegree,
                std::next(child->values.begin(), medianIndex + 1), child->values.end(),
                std::next(child->children.begin(), medianIndex + 1), child->children.end());
        }
        else {
            // build [4, 5]
            newLeft = new btreenode<T>(this, minDegree,
                child->values.begin(), std::next(child->values.begin(), medianIndex));

            // child [7, 8]
            newRight = new btreenode<T>(this, minDegree,
                std::next(child->values.begin(), medianIndex + 1), child->values.end());
        }

        // add 6 to [3, 9] making [3, 6, 9]
        values.insert(std::next(values.begin(), childIndex), valueToPullup);

        //// sanity check
        //validateValues();

        auto toremove = std::next(children.begin(), childIndex);
        // remove the pointer to the old node
        node_ptr toremove_ptr = *toremove;
        children.erase(toremove);
        delete toremove_ptr;

        // add the child point to [4, 5] and [7, 8]
        // add right first to maintain ordering
        children.insert(std::next(children.begin(), childIndex), newRight);
        children.insert(std::next(children.begin(), childIndex), newLeft);
    }

    void splitFullRoot() {
        // The root of the tree, and in fact the entire tree, is
        //
        // [1 2 3 4 5]
        //
        // So pull out 3 and split the left and right side
        //
        //     [3]
        // [1 2] [4 5]

        int medianIndex = values.size() / 2;
        auto medianNode = std::next(values.begin(), medianIndex);

        node_ptr newLeft, newRight;

        if (children.size() > 0) {
            // build the left node [1 2]
            newLeft = new btreenode<T>(parent, minDegree,
                values.begin(), std::next(values.begin(), medianIndex),
                children.begin(), std::next(children.begin(), medianIndex + 1));

            // build the right node [4 5]
            newRight = new btreenode<T>(this, minDegree,
                std::next(values.begin(), medianIndex + 1), values.end(),
                std::next(children.begin(), medianIndex + 1), children.end());
        }
        else {
            // build the left node [1 2]
            newLeft = new btreenode<T>(parent, minDegree,
                values.begin(), std::next(values.begin(), medianIndex));

            // build the right node [4 5]
            newRight = new btreenode<T>(this, minDegree,
                std::next(values.begin(), medianIndex + 1), values.end());
        }

        // [1 2 3 4 5] -> [3 4 5]
        values.erase(values.begin(), medianNode);

        // [3 4 5] -> [3]
        values.erase(std::next(values.begin(), 1), values.end());

        // the children are now all handled by newLeft and newRight
        children.clear();

        // Add the left child [1 2]
        children.push_back(newLeft);

        // Add the right child [4 5]
        children.push_back(newRight);
    }

    void add(const T& value) {
        values.insert(lower_bound(values.begin(), values.end(), value), value);        
    }

    node_ptr findNodeContaining(const T& value) {
        for(T v : values) {
            if (v == value) {
                return this;
            }
        }

        for(node_ptr n : children) {
            node_ptr f = n->findNodeContaining(value);
            if (f != nullptr) {
                return f;
            }
        }

        return nullptr;
    }

    bool contains(const T& value) {
        return findNodeContaining(value) != nullptr;
    }

    node_ptr pushDownToLeaf(const T& value) {

    }

    void push_down(int valueIndex) {
        //     [3     6]
        // [1 2] [4 5] [7 8]
        // becomes
        //           [6]
        // [1 2 3 4 5] [7 8]

        // 3
        auto node_push_down = std::next(values.begin(), valueIndex);

        // [1 2]
        node_ptr left_child = *std::next(children.begin(), valueIndex);

        // [4 5]
        node_ptr right_child = *std::next(children.begin(), valueIndex + 1);

        // [1 2] -> [1 2 3]
        left_child->addEnd(*node_push_down, nullptr);

        // [1 2 3] -> [1 2 3 4 5]
        left_child->values.insert(left_child->values.end(), 
            right_child->values.begin(), right_child->values.end());
        
        left_child->children.insert(left_child->children.end(), 
            right_child->children.begin(), right_child->children.end());

        // remove 3 from current
        values.erase(node_push_down);

        // free [4 5] since they have moved to the left child
        delete right_child;
        children.remove(right_child);
    }

    void addEnd(const T& value, node_ptr child) {
        values.push_back(value);
        if (child != nullptr) {
            children.push_back(child);
        }
    }

    void addFront(const T& value, node_ptr child) {
        values.push_front(value);
        if (child != nullptr) {
            children.push_front(child);
        }
    }

    bool remove(const T& value) { return false; }

    void removeFirst() {
        values.pop_front();
        children.pop_front();
    }

    void removeLast() {
        values.pop_back();
        if (children.size()) {
            children.pop_back();
        }
    }
};

template<class T>
class btree {
    typedef btreenode<T>* node_ptr;

    int size = 0;
    node_ptr root;
    const int minimumDegree = 4;

    void insertNonFull(node_ptr node, const T& value) {
        if (node->leaf()) {
            node->add(value);
        }
        else {
            int insert_index =
                std::distance(node->values.begin(),
                    lower_bound(node->values.begin(), node->values.end(), value));

            node_ptr child = *std::next(node->children.begin(), insert_index);

            if (child->full()) {
                node->splitChild(insert_index);
                T newValue = *std::next(node->values.begin(), insert_index);
                if (value > newValue) {
                    child = *std::next(node->children.begin(), insert_index+1);
                }
            }

            insertNonFull(child, value);
        }
    }

    template<class _Func>
    void _iter(node_ptr n, _Func callback) {
        if (n->leaf()) {
            for (T v : n->values) {
                callback(v);
            }
        }
        else {
            size_t c = 0;
            for (; c < n->values.size(); c++) {
                _iter(*std::next(n->children.begin(), c), callback);
                callback(*std::next(n->values.begin(), c));
            }

            // and then the last child
            _iter(*std::next(n->children.begin(), c), callback);
        }
    }

public:
    btree() : root(nullptr) {}

    bool contains(const T& value) {
        return root->contains(value);
    }

    bool remove(const T& value) {
        return root->remove(value);
    }

    template<class _Func>
    void iter(_Func callback) {
        _iter(root, callback);
    }

    void add(const T& value) {
        if (root == nullptr) {
            root = new btreenode<T>(minimumDegree);
            root->add(value);
        }
        else {
            if (root->full()) {
                root->splitFullRoot();
            }

            insertNonFull(root, value);
        }

        size++;
    }
};