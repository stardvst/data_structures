#include <iostream>
#include <set>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));

    set<int> tree;

    for (int i = 0; i < 10; i++)
    {
        tree.insert(rand());
    }

    for (int value : tree)
    {
        cout << value << " ";
    }
}