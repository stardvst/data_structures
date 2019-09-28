#pragma once

#include "model\Review.h"
#include "ocr\OcrResult.h"
#include "mocks\ReviewGenerator.h"
#include "mocks\Waiter.h"

class OcrReviewParser {
    ReviewGenerator gen;
public:
    Review parse(const OcrResult& ocrResult) {
        Worker.Busy(5, 10);
        return std::move(gen.Generate());
    }
};