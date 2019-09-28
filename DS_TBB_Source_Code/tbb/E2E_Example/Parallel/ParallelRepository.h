#pragma once

#include <map>
#include <list>
#include <numeric>
#include <functional>

#include "ReviewRepository.h"
#include "model\Review.h"
#include "mocks\Waiter.h"
#include "tbb\tbb.h"

class ParallelRepository : public ReviewRepository {
    tbb::concurrent_vector<Review> reviews;

    ParallelRepository(const ParallelRepository& other) = delete;

public:
    ParallelRepository() {}

    ParallelRepository(ParallelRepository&& other)
        : reviews(std::move(other.reviews)) {}

    void save(const Review& details) {
        Worker.Sleep(10, 20);
        reviews.push_back(details);
    }

    void hist(std::map<int, int>& result) const {

        // use the TLS combinable to allow each thread
        // to not need to lock on a shared resource
        tbb::combinable<std::map<int,int>> tls_result;

        tbb::parallel_for_each(reviews.begin(), reviews.end(), 
            [&tls_result](const Review& review) {
                tls_result.local()[review.stars]++;
            }
        );

        // combine the TLS values into the final result
        tls_result.combine_each([&result](std::map<int, int>& tls) {
            for (int i = 1; i < 6; i++) {
                result[i] += tls[i];
            }
        });
    }

    double avg() const {

        // parallel reduce to sum the total star ratings
        double sum = tbb::parallel_reduce(
            reviews.range(),
            0,
            [](const tbb::concurrent_vector<Review>::const_range_type& range, long value)->long {
                return value + std::accumulate(range.begin(), range.end(), 0,
                    [](long sum, const Review& review){ 
                        return sum + review.stars; 
                    });
        },
        std::plus<long>());

        // divide the sum
        return sum / reviews.size();
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

