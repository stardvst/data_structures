#include "avl.h"
#include <random>
#include <algorithm>
#include <iostream>

void main() {
    avl<int> tree;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);

    int previous_height = 0;
    int count = 0;

    while (tree.height() < 12) {
        count++;
        if (previous_height < tree.height()) {
            std::cout << count << "," << tree.height() << std::endl;
            previous_height = tree.height();
        }

        tree.add(count);
    }

    int previous = INT_MIN;

    for (int n : tree) {
        if (n < previous) {
            std::cout << "ERROR: " << previous << " is greater than " << n << std::endl;
        }
        previous = n;
    }

    while(tree.size() > 0) {
        if (!tree.remove(previous--)) {
            std::cout << previous << " - whoa!" << std::endl;
        }
        if (previous_height > tree.height()) {
            std::cout << tree.size() << "," << tree.height() << std::endl;
            previous_height = tree.height();
        }
    }
}