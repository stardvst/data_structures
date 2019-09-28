#pragma once

#include "Image.h"
#include "mocks\Waiter.h"

class Scanner {
    int limit;
public:
    Scanner(int limit) : limit(limit){}
    bool try_acquire(Image* img) {
        if (limit-- > 0) {
            Worker.Sleep(5, 10);
            return true;
        }

        return false;
    }
};