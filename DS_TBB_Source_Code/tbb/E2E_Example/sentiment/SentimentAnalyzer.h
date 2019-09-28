#pragma once

#include "model/Review.h"
#include "mocks/RandomWord.h"

class SentimentAnalyzer {
    NumberGenerator<std::uniform_real_distribution<double>, double> gen;
public:
    SentimentAnalyzer()
        : gen(-1, 1) {}

    double analyze(const Review& review) {
        return gen.get();
    }
};