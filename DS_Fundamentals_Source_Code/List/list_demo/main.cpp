#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include "slist.h"
#include "dlist.h"
#include <cstdlib>
#include <ctime>


#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

using namespace std;

template<class _T>
void print_list(_T first, _T end)
{
    for (_T current = first; 
         current != end;
         current = current->next)
    {
        cout << current->data << " ";
    }

    cout << endl;
}

void slist_demo()
{
    lists::slist<string> list;

    // 3
    list.push_front("3");

    // 1 -> 3
    list.push_front("1");

    // 1 -> 2 -> 3
    list.insert_after(list.begin(), "2");

    print_list<lists::slist<string>::node_ptr>(list.begin(), list.end());

    // 1 -> 3
    list.remove_after(list.begin());

    print_list<lists::slist<string>::node_ptr>(list.begin(), list.end());

    // 3
    list.pop_front();

    print_list<lists::slist<string>::node_ptr>(list.begin(), list.end());
}

void dlist_demo()
{
    lists::dlist<string> list;

    // 2
    list.push_front("2");

    // 1 -> 2
    list.push_front("1");

    // 1 -> 2 -> 3
    list.push_back("3");

    print_list<lists::dlist<string>::node_ptr>(list.begin(), list.end());

    // 1 -> 3
    list.remove(list.begin()->next);
    print_list<lists::dlist<string>::node_ptr>(list.begin(), list.end());

    // 1
    list.pop_back();
    print_list<lists::dlist<string>::node_ptr>(list.begin(), list.end());

    // empty
    list.pop_front();
    print_list<lists::dlist<string>::node_ptr>(list.begin(), list.end());
}

std::vector<std::string> load_words(std::string path);


void insert_sorted_tests()
{
    lists::dlist<string> sorted_list;

    vector<string> words = load_words("washington.txt");
    for (string word : words)
    {
        // find the location
        lists::dlist<string>::node_ptr iter = sorted_list.begin();
        while (iter != sorted_list.end() && iter->data < word)
        {
            iter = iter->next;
        }

        // insert before
        sorted_list.insert_before(iter, word);
    }

    print_list<lists::dlist<string>::node_ptr>(sorted_list.begin(), sorted_list.end());
}

template <class T>
using linked_list = lists::dlist<T>;

void sort_list_demo();

void reverse_demo()
{
    lists::slist<int> ordered;
    for (int i = 0; i < 100; i++)
    {
        ordered.push_front(i);
    }

    print_list<lists::slist<int>::node_ptr>(ordered.begin(), ordered.end());

    ordered.reverse();

    print_list<lists::slist<int>::node_ptr>(ordered.begin(), ordered.end());
}

int main()
{
    //slist_demo();
    //dlist_demo();
    //insert_sorted_tests();

    // sort_list_demo();

    reverse_demo();

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif
}

 