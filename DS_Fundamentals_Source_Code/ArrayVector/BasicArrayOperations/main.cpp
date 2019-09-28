#include <iostream>
#include <ctime>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

struct gauge_reading
{
    int reading;
    time_t when;
};

void printarray(int *data, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << i << ": " << data[i] << std::endl;
    }
}

void allocate_stack()
{
    // expression must be const
    const int size = 10;

    // allocated on the stack without initializing the memory
    int stack[size];
    printarray(stack, size);

    // allocated on the stack with 0 initialized memory
    int stack_init_zero[size] = { 0 };
    printarray(stack_init_zero, size);

    // allocated on the stack with explicitly initialized values
    int stack_init_values[size] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    printarray(stack_init_values, size);

    // Compile Error: too many initializers
    // int stack_init_values[size] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    
}

void allocate_heap()
{
    // expression does not need to be const
    int size = 10;
    int *heap_array = new int[size];
    
    // pointer syntax used (not array)
    int *heap = new int[size];
    printarray(heap, size);

    // pointer syntax, only initializes the first member
    int *heap_init_zero = new int[size] {0};
    printarray(heap_init_zero, size);

    // pointer syntax, explicitly initialize all members
    int *heap_init_explicit = new int[size] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    printarray(heap_init_explicit, size);

    // Runtime Error: buffer overflow (undefined behavior)
    int *heap_init_overflow = new int[size] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
}

void index_types()
{
    // expression does not need to be const
    int size = 10;
    int *heap_array = new int[size];

    for (int i = 0; i < size; i++) 
    { 
        heap_array[i] = i; 
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << heap_array[i] << std::endl;
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << *(heap_array+i) << std::endl;
    }

    int *current = heap_array;
    for (int i = 0; i < size; i++)
    {
        std::cout << (*current) << std::endl;
        current++;
    }

    delete[] heap_array;

}

void multi_dimensional_array()
{
    // sizes
    int rows = 4;
    int columns = 5;

    // the multi-dimensional array
    gauge_reading **readings;
    
    // allocation
    readings = new gauge_reading*[rows];
    for (int i = 0; i < rows; i++)
    {
        readings[i] = new gauge_reading[columns];
    }

    // ... use the values ...

    // free each row
    for (int i = 0; i < rows; i++)
    {
        delete[] readings[i];
    }

    // free the columns
    delete[] readings;
}

void multi_dimensional_array_of_pointers()
{
    // sizes
    int rows = 4;
    int columns = 5;

    // the multi-dimensional array
    gauge_reading ***readings;

    // allocation
    readings = new gauge_reading**[rows];

    for (int i = 0; i < rows; i++)
    {
        // create the row
        readings[i] = new gauge_reading*[columns];

        for (int x = 0; x < columns; x++)
        {
            // then allocate each reading
            readings[i][x] = new gauge_reading();
        }
    }

    // ... use the values ...

    // cleanup
    for (int i = 0; i < rows; i++)
    {
        // delete each reading in the row
        for (int x = 0; x < columns; x++)
        {
            delete readings[i][x];
        }

        // then delete the row
        delete[] readings[i];
    }

    // free the columns
    delete[] readings;
}

void jaggedd_multi_dimensional_array()
{
    // sizes
    int rows = 4;

    // the multi-dimensional array
    gauge_reading **readings;

    // allocation
    readings = new gauge_reading*[rows];
    for (int i = 0; i < rows; i++)
    {
        // create a stepped jagged array
        readings[i] = new gauge_reading[rows + 1];
    }

    // ... use the values ...

    // free each row
    for (int i = 0; i < rows; i++)
    {
        delete[] readings[i];
    }

    // free the columns
    delete[] readings;
}

int* allocate_on_stack()
{
    // WARNING: returning address of local (temporary) variable
    int array[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    return array;
}

void use_stack_array(int array[])
{
    int new_array[10] = { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109 };
    printarray(array, 10);
}

void stack_lifetime()
{
    int *from_stack = allocate_on_stack();
    use_stack_array(from_stack);
}


void allocate_stack_init_list_complex()
{
    gauge_reading readings[5] = 
    { 
        { 1, 10 },
        { 2, 20 },
        { 3, 30 },
        { 4, 40 },
        { 5, 50 },
    };
    for (int i = 0; i < 5; i++)
    {
        std::cout << "Reading " << i << ": " 
                  << readings[i].reading 
                  << " at " << readings[i].when << std::endl;
    }
}

void stdarray();
void boostarray();

void main()
{
    boostarray();
//    multi_dimensional_array_of_pointers();
    _CrtDumpMemoryLeaks();
//    multi_dimensional_array();
//    index_types();

    //allocate_stack();
    //allocate_heap();
    //stack_lifetime();
    //allocate_stack_init_list_complex();
}