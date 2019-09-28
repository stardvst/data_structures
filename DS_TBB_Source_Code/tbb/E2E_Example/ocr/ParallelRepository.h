#pragma once

#include <map>
#include <list>
#include <numeric>
#include <functional>

#include "ReviewRepository.h"
#include "model\Review.h"
#include "mocks\Waiter.h"
#include "tbb\tbb.h"

class ReviewRepository : public ReviewRepository {
    tbb::concurrent_vector<Review> reviews;

    ReviewRepository(const ReviewRepository& other) = delete;

public:
    ReviewRepository() {}

    ReviewRepository(ReviewRepository&& other)
        : reviews(std::move(other.reviews)) {}

    void save(const Review& details) {
        Worker.Sleep(10, 20);
        reviews.push_back(details);
    }

    template<class HistType>
    void hist(HistType& result) const {
        tbb::combinable<std::map<int,int>> tls_result;

        tbb::parallel_for_each(reviews.begin(), reviews.end(), 
            [&tls_result](const Review& review) {
                tls_result.local()[review.stars]++;
            }
        );

        tls_result.combine_each([&result](std::map<int, int>& tls) {
            for (int i = 1; i < 6; i++) {
                result[i] += tls[i];
            }
        });
    }

    double avg() const {
        double count = tbb::parallel_reduce(
            reviews.range(),
            0,
            [](const tbb::concurrent_vector<Review>::const_range_type& range, long value)->long {
                return value + std::accumulate(range.begin(), range.end(), 0,
                    [](long sum, const Review& review){ 
                        return sum + review.stars; 
                    });
        },
        std::plus<long>());

        return count / reviews.size();
    }

    template<class Func>
    void top(size_t n, Func callback) const {
        TopN<std::greater<double>> topn(n, std::greater<double>());

        for (auto review : reviews) {
            topn.check(review);
        }

        for (auto review : topn) {
            callback(review);
        }
    }
};

template <typename Comparator>
class TopN {
    std::list<const Review> reviews;
    Comparator compare;
    double cur_min = -1;
    const size_t count;

    void insert(const Review& review) {
        std::list<const Review>::const_iterator current;
        for (current = reviews.cbegin(); current != reviews.end(); current++) {
            //if ((*current).review.Sentiment >= review.review.Sentiment) {
            //    break;
            //}

            if (compare((*current).review.Sentiment, review.review.Sentiment)) {
                break;
            }
        }

        reviews.insert(current, review);

        if (count < reviews.size()) {
            reviews.pop_front();
            cur_min = reviews.front().review.Sentiment;
        }
    }

public:
    TopN(size_t n, Comparator compare)
        : count(n), compare(compare)
    {
    }

    void check(const Review& review) {
        if (review.review.Sentiment >= cur_min) {
            insert(review);
        }
    }

    std::list<const Review>::const_iterator begin() {
        return reviews.begin();
    }

    std::list<const Review>::const_iterator end() {
        return reviews.end();
    }
};