#pragma once
#include <algorithm>
#include <functional>

template<class T, 
         class Compare = std::less<T>>
class heap {
    size_t count = 0;
    size_t capacity = 0;

    // 7 is a 3-level full tree
    //     1
    //   2   3
    //  4 5 6 7
    const size_t DEFAULT_CAPACITY = 7;

    T* data = nullptr;

    Compare compare;

    void grow_if_needed() {
        if (count >= capacity) {
            size_t new_capacity = std::max(
                // grow by full tree sizes
                // 1 -> 3 -> 7 -> 15 -> 31
                2 * capacity + 1,
                DEFAULT_CAPACITY);

            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < capacity; i++) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
    }

    inline size_t parent(const size_t index) {
        return (index - 1) / 2;
    }

    inline size_t left(const size_t index) {
        return 2 * index + 1;

    }

    inline size_t right(const size_t index) {
        return 2 * index + 2;
    }

    size_t indexOfChildToSwap(const size_t index) {
        // To avoid having to swap twice, 
        // we swap with the largest value.
        // E.g.,
        //      5
        //    6   8
        // 
        // if we swapped with 6 first we'd have
        //
        //     6
        //   5   8
        //
        // And we'd require another swap to 
        // get the desired tree
        //
        //    8
        //  6   5
        //
        // So we find the largest child and just do 
        // the right thing off the bat
        size_t right_index = right(index);
        size_t left_index = left(index);

        // if the right child is in the heap
        if (right_index < count) {

            // Use compare to find the greatest/least child
            return compare(data[left_index], data[right_index])
                ? left_index : right_index;

        }

        return left_index;
    }

public:
    void push(const T& value) {
        grow_if_needed();

        // add the value to the end of the array
        data[count] = value;

        // and now move it up the tree into it's
        // appropriate location
        size_t index = count;

        // while we're not at the tree root and the value 
        // should be in it's parent's position...
        while (index > 0 && compare(data[index], data[parent(index)])) {
            std::swap(data[index], data[parent(index)]);
            index = parent(index);
        }

        count++;
    }

    T& top() {
        if (empty()) {
            throw std::out_of_range("The heap is empty");
        }

        return data[0];
    }

    void pop() {
        if (empty()) {
            return;
        }

        // shift the last value into the head slot
        // In this example we're popping "7" off
        // E.g., 
        // [7 5 6 4] -> [4 5 6]
        data[0] = data[--count];

        // rebalance
        // E.g., 
        // [4 5 6] -> [6 5 4]
        size_t index = 0;
        while (index < count) { 
            // beyond the end of the heap
            if (left(index) >= count) {
                break;
            }

            // [4 5 6] - we want to swap with 6, not 5
            size_t childIndex = indexOfChildToSwap(index);

            // In [4 5 6] compare 4 and 6
            if (compare(data[index], data[childIndex]))
            {
                // heap ordering is satisfied
                break;
            }

            // swap 4 and 6
            // [4 5 6] -> [6 5 4]
            std::swap(data[index], data[childIndex]);

            // start again at 4 (index 2)
            index = childIndex;
        }
    }

    size_t size() {
        return count;
    }

    bool empty() {
        return count == 0;
    }
};