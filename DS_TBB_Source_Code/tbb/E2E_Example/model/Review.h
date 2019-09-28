#pragma once

#include <string>
#include <ostream>
#include "Model\Reviewer.h"

class Review {
public:
    Review() : stars(0) { }

    Review(const Review& other)
        : stars(other.stars),
        review(other.review),
        reviewer(other.reviewer)
    {
    }

    Review(Review&& other) 
        : stars(other.stars), 
        review(std::move(other.review)),
        reviewer(std::move(other.reviewer))
    {
    }
    
    int stars;
    ReviewContent review;
    Reviewer reviewer;
};

std::ostream& operator<<(std::ostream& strm, const Review& review);