#include "tbb\tbb.h"
#include <iostream>

template<typename Iterator, typename Func>
void serial_do(Iterator start, Iterator end, Func func)
{
    while (start != end)
    {
        func(*start++);
    }
}

template<class Iterator, typename Func>
class parallel_do_task : public tbb::task {
    Iterator start_;
    Iterator end_;
    Func func_;
public:
    parallel_do_task(Iterator start, Iterator end, Func func)
        : start_(start), end_(end), func_(func) { }

    task* execute() {

        if (start_ < end_)
        {
            set_ref_count(2);

            // allocate the child
            parallel_do_task& child = *new(allocate_child()) parallel_do_task(start_ + 1, end_, func_);

            spawn(child);

            func_(*start_);

            wait_for_all();
        }

        return nullptr;
    }
};

template<typename Iterator, typename Func>
void parallel_do(Iterator start, Iterator end, Func func)
{
    parallel_do_task<Iterator, Func>& t = 
        *new(tbb::task::allocate_root()) 
            parallel_do_task<Iterator, Func>(start, end, func);

    tbb::task::spawn_root_and_wait(t);
}

void do_example()
{
    int data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    parallel_do(data, data + 10, [](int x)
    {
        std::cout << x << std::endl;
    });
}