#pragma once

#include "Model\Review.h"

std::ostream& operator<<(std::ostream& strm, const Review& review) {
    strm << review.reviewer << std::endl;
    strm << review.stars << std::endl;
    strm << review.review;

    return strm;
}