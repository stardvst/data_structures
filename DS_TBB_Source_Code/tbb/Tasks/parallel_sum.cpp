#include "tbb\tbb.h"
#include <iostream>
#include <cstdlib>

// #define BLOCKING
// #define USE_CONTINUATION
#define RECYCLE_PARENT_AS_CHILD

class parallel_sum_base : public tbb::task {
protected:
    // private fields and functions
    int *_data;
    long *_sum;
    int _start; // inclusive
    int _end;   // exclusive

    const int _grainsize = 500;

    parallel_sum_base(int* data, int start, int end, long *sum)
        : _data(data), _sum(sum), _start(start), _end(end) { }

    int range_size() {
        return _end - _start;
    }

    int midpoint() {
        return _start + range_size() / 2;
    }

    void process_linear() {
        long sum = 0;

        for (int i = _start; i < _end; i++) {
            sum += _data[i];
        }

        *_sum += sum;
    }
};

#ifdef BLOCKING

class parallel_sum_task : public parallel_sum_base {
private:
    parallel_sum_task& create_child(int start, int end, long *sum) {
        return *new(tbb::task::allocate_child())
            parallel_sum_task(_data, start, end, sum);
    }

public:
    parallel_sum_task(int* data, int start, int end, long *sum)
        : parallel_sum_base(data, start, end, sum) { }

    tbb::task* execute() {
        if (range_size() < _grainsize) {
            process_linear();
        } else {
            set_ref_count(3);

            long left_result = 0, right_result = 0;

            auto& left = create_child(_start, midpoint(), &left_result);
            auto& right = create_child(midpoint(), _end, &right_result);

            spawn(left);
            spawn_and_wait_for_all(right);

            *_sum = (left_result + right_result);
        }

        return nullptr;
    }
};

#endif


struct parallel_sum_continuation : public tbb::task {
    long *sum;
    long left, right;

    parallel_sum_continuation(long *output)
        : sum(output), left(0), right(0) {}

    tbb::task* execute() {
        *sum = left + right;
        return nullptr;
    }
};

#ifdef USE_CONTINUATION



class parallel_sum_task : public parallel_sum_base {
private:
    parallel_sum_task& create_child(task* parent, int start, int end, long *sum) {
        return *new(parent->allocate_child()) parallel_sum_task(_data, start, end, sum);
    }

    parallel_sum_continuation& create_continuation() {
        return *new(allocate_continuation()) parallel_sum_continuation(_sum);
    }

public:
    parallel_sum_task(int* data, int start, int end, long *sum)
        : parallel_sum_base(data, start, end, sum) { }

    tbb::task* execute() {
        if (range_size() < _grainsize) {
            process_linear();
        } else {
            // the continuation will join the left and right sums 
            auto& c = create_continuation();

            c.set_ref_count(2);

            auto& left = create_child(&c, _start, midpoint(), &c.left);
            auto& right = create_child(&c, midpoint(), _end, &c.right);

            c.spawn(left);
            c.spawn(right);
        }

        return nullptr;
    }
};

#endif

#ifdef RECYCLE_PARENT_AS_CHILD




class parallel_sum_task : public parallel_sum_base {
private:
    parallel_sum_task& create_child(task* parent, int start, int end, long *sum) {
        return *new(parent->allocate_child())
            parallel_sum_task(_data, start, end, sum);
    }

    parallel_sum_continuation& create_continuation() {
        return *new(allocate_continuation()) parallel_sum_continuation(_sum);
    }

public:
    parallel_sum_task(int* data, int start, int end, long *sum)
        : parallel_sum_base(data, start, end, sum) { }

    tbb::task* execute() {
        if (range_size() < _grainsize) {
            process_linear();
            return nullptr;
        }
        else {
            // the continuation will pull the left and right sums 
            // together in it's execute function
            auto& c = create_continuation();

            // 2 children - left and right (recycled parent)
            c.set_ref_count(2);

            // create only the left child.  The right child will be
            // created by re-using this task
            auto& left = create_child(&c, _start, midpoint(), &c.left);
            spawn(left);

            // re-use this task instead of creating a new child
            recycle_as_child_of(c);
            _start = midpoint();
            _sum = &c.right;

            return this;
        }
    }
};

#endif

long parallel_sum(int *values, int length)
{
    long result = 0;

    auto& root = *new(tbb::task::allocate_root()) parallel_sum_task(values, 0, length, &result);
    tbb::task::spawn_root_and_wait(root);

    return result;
}

void partitioned_sum() {

    const int LENGTH = 200000;
    int values[LENGTH];

    long expected = 0;
    for (int i = 0; i < LENGTH; i++) {
        int value = rand();
        values[i] = value;
        expected += value;
    }

    long sum = parallel_sum(values, LENGTH);

    std::cout << "Expected: " << expected << std::endl
              << "Actual:   " << sum << std::endl
              << "Equal:    " << (expected == sum) << std::endl;
}