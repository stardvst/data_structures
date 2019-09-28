#include "btree.h"
#include <iostream>

void main() {
    btree<int> tree;

    for (int i = 0; i < 100; i++) {
        tree.add(i);
    }

    for (int i = 0; i < 110; i++) {
        std::cout << i << " is in tree: " << tree.contains(i) << std::endl;
    }

    for (int i = 0; i < 100; i += 2) {
        tree.remove(i);
    }

    tree.iter([](int i) {
        std::cout << i << std::endl;
    });
}