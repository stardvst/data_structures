#pragma once

#include "model\Review.h"
#include "RandomWord.h"

class ReviewGenerator {

public:
    Review Generate() {
        Review review;
        
        review.reviewer.Address.Address1 = Generator.Address1();
        review.reviewer.Address.City = Generator.City();
        review.reviewer.Address.State = Generator.State();
        review.reviewer.Address.Zip5 = Generator.Zip5();
        review.reviewer.Name.FirstName = Generator.FirstName();
        review.reviewer.Name.LastName = Generator.LastName();
        review.reviewer.Phone = Generator.PhoneNumber();
        review.reviewer.Email = Generator.Email(review.reviewer.Name.FirstName, review.reviewer.Name.LastName);
        review.stars = Generator.Stars();
        review.review.Content = Generator.ReviewContent();

        return std::move(review);
    }
};