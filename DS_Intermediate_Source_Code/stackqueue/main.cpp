#include "stack.h"
#include "queue.h"
#include <iostream>
using namespace std;

void main() {
    stack<int> stk;
    queue<int> que;

    for (int i = 0; i < 10; i++) {
        stk.push(i);
        que.enque(i);
    }

    cout << "s q\n---" << endl;

    while (!stk.empty()) {
        cout << stk.front() << " " << que.front() << endl;
        stk.pop();
        que.deque();
    }
}