#include "array\queue.h"
#include <iostream>
using namespace std;

void main() {
    queue<int> que;

    // 1, 2, 3, 4, 5, 6, 7, ...
    for (int i = 0; i < 100; i++) {
        que.push(i);
    }

    // 1, 2, 3, 4, 5, 6, 7, ...
    while (!que.empty()) {
        cout << que.front() << endl;
        que.pop();
    }
}