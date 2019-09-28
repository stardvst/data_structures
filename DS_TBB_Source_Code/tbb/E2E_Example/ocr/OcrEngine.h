#pragma once

#include "OcrResult.h"
#include "..\mocks\Waiter.h"

class OcrEngine {
public:
    OcrResult parse(unsigned char* image, size_t size) {
        Worker.Busy(15, 30);
        OcrResult result;

        return std::move(result);
    }
};