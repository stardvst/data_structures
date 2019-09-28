#pragma once

template<class T>
class deque {
private:
    // the array of data
    T* data;
    
    // the current head index
    size_t start;

    // the current tail index
    size_t end;

    // the number of items in the array
    size_t count;

    // the capacity of the array
    size_t allocated;

    const size_t MINIMUM_SIZE = 4;
    const double GROWTH_FACTOR = 1.5;

    size_t new_size() {
        size_t new_size = static_cast<size_t>(allocated * GROWTH_FACTOR);
        if (new_size < MINIMUM_SIZE) {
            new_size = MINIMUM_SIZE;
        }

        return new_size;
    }

    void grow_if_needed() {
        if (count < allocated) {
            return;
        }

        size_t new_count = new_size();
        T* new_data = new T[new_count];

        if (count > 0) {
            size_t current = 0;

            if (start < end) {
                for (size_t i = start; i <= end; i++) {
                    new_data[current++] = data[i];
                }
            }
            else {
                for (size_t i = start; i < allocated; i++) {
                    new_data[current++] = data[i];
                }

                for (size_t i = 0; i <= end; i++) {
                    new_data[current++] = data[i];
                }
            }

            delete[] data;
        }

        data = new_data;

        start = 0;
        end = count;
        allocated = new_count;
    }

    // one before the start index
    // accounting for wrap around.
    // the buffer must already be grown
    size_t before_start() {
        if (count == 0) {
            return 0;
        }

        if (start > 0) {
            return start - 1;
        }

        return allocated - 1;
    }

    // one after the start index
    // accounting for wrap around.
    // the buffer must already be grown
    size_t after_end() {
        if (count == 0) {
            return 0;
        }

        if (end < allocated) {
            return end + 1;
        }

        return 0;
    }

public:
    deque() : start(0), end(0), count(0), allocated(0), data(nullptr) {}

    ~deque() {
        if (data) {
            delete[] data;
        }
    }

    void push_front(const T& val) {
        grow_if_needed();
        data[before_start()] = val;
    }

    void push_back(const T& val) {
        grow_if_needed();
        data[after_end()] = val;
    }

    T& front() const {
        return data[start];
    }

    T& back() const {
        return data[end];
    }

    void pop_front() {
        // empty so nothing to do
        if (count == 0) {
            return;
        }

        if (start + 1 < allocated) {
            // if not at end of buffer
            // move the start position forward
            start++;
        }
        else {
            // otherwise wrap around
            start = 0;
        }

        count--;

        if (count == 0) {
            // if we are empty then
            // reset the indexes
            start = 0;
            end = 0;
        }

    }

    void pop_back() {
        if (count == 0) {
            return;
        }

        if (end == 0) {
            // 3xxxx12
            end = allocated - 1;
        }
        else {
            // 123xxxx
            end--;
        }

        count--;

        if (count == 0) {
            start = 0;
            end = 0;
        }
    }

    size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }
};