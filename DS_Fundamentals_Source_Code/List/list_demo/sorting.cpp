#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

#include "dlist.h"

void populate_list(lists::dlist<int> &list, int count)
{
    srand(time(NULL));

    for (int i = 0; i < count; i++)
    {
        list.push_back(rand());
    }
}

void verify_sorted(lists::dlist<int> &list)
{
    int prev = INT_MIN;

    for (lists::dlist<int>::node_ptr current = list.begin();
        current != list.end();
        current = current->next)
    {
        std::cout << current->data << " ";

        assert(prev <= current->data);
        prev = current->data;
    }
}

void insertion_sort_list(lists::dlist<int> &list)
{
    // start at the beginning
    lists::dlist<int>::node_ptr current = list.begin();

    // if the list is empty, return
    if (current == list.end())
    {
        return;
    }

    // the first node is the largest currently known value.
    int largest = current->data;

    while (current != list.end())
    {
        // keep track of the next node in case we delete
        // the current node (see note below about performance)
        lists::dlist<int>::node_ptr next = current->next;

        if (current->data < largest)
        {
            // find the insertion pint
            lists::dlist<int>::node_ptr insert_point = list.begin();

            // skip all the items less than or equal to
            // the current value
            while (current->data >= insert_point->data)
            {
                insert_point = insert_point->next;
            }

            // insert it before the larger value
            list.insert_before(insert_point, current->data);

            // and remove the old node
            // this could be done more efficently with pointer swaps 
            // if sort was part of the linked list class
            list.remove(current);
        }

        // the next unsorted node
        current = next;

        // largest = last value in sorted value
        largest = current->prev->data;
    }
}

void sort_list_demo()
{
    lists::dlist<int> list;
    populate_list(list, 1000);

    insertion_sort_list(list);

    verify_sorted(list);
}