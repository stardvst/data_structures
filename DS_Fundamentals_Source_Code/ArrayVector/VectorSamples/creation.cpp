#include <vector>

void creation()
{
    std::vector<int> data;
    
    data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    int value = data[4];
}

void data_method()
{
    std::vector<int> data;

    const int* ptr = data.data();
}

void allocator()
{
    std::allocator<int> alloc;

    int count = 1;

    int* allocated = alloc.allocate(count);

    alloc.deallocate(allocated, count);
}

void pop_back()
{
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8 };

    data.pop_back();
}
