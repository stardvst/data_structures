#pragma once

#include <map>
#include <list>
#include <numeric>
#include <functional>
#include <vector>

#include "ReviewRepository.h"
#include "model\Review.h"
#include "mocks\Waiter.h"

class SerialRepository : public ReviewRepository {
    std::vector<Review> reviews;
    SerialRepository(const SerialRepository& other) = delete;

public:
    SerialRepository() {}

    SerialRepository(SerialRepository&& other)
        : reviews(std::move(other.reviews)) {}

    void save(const Review& details) {
        Worker.Sleep(10, 20);
        reviews.push_back(details);
    }

    void hist(std::map<int,int>& result) const {
        for (auto review : reviews) {
            result[review.stars]++;
        }
    }

    double avg() const {
        long count = std::accumulate(
            reviews.cbegin(), 
            reviews.cend(), 
            0, 
            [](long sum, const Review& review){
                return sum + review.stars;
            });

        return count / reviews.size();
    }

    void top(size_t n, ReviewCallback callback) const {
        TopN topn(n);

        for (auto review : reviews) {
            topn.check(review);
        }

        for (auto review : topn) {
            callback(review);
        }
    }
};

