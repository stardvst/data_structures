#pragma once

#include "model\Review.h"
#include <functional>

// callback fired when top finds a new top item
typedef void(*ReviewCallback)(const Review&);

/*
 * Review storage.  Could be a local SQL database, 
 * cloud storage, in-memory storage or anything else.
 */
class ReviewRepository {
public:
    // saves a new Review in the repository
    virtual void save(const Review& details) = 0;

    // generates a histogram of the star ratings
    virtual void hist(std::map<int,int>& result) const = 0;

    // the average star rating for the entire repository
    virtual double avg() const = 0;

    // the top N reviews by sentiment
    virtual void top(size_t n, ReviewCallback callback) const = 0;
};


/*
 * Utility class that can be used by the ReviewRepository::top function
 */
class TopN {
    std::list<const Review> reviews;
    double cur_min = -1;
    const size_t count;

    void insert(const Review& review) {
        std::list<const Review>::const_iterator current;

        // find the insertion point
        for (current = reviews.cbegin(); current != reviews.end(); current++) {
            if ((*current).review.Sentiment> review.review.Sentiment) {
                break;
            }
        }

        reviews.insert(current, review);

        // if we now have more than we need, trim the front value
        // and update the cur_min so we can avoid calling insert
        // when we know the value is too small to matter.
        if (count < reviews.size()) {
            reviews.pop_front();
            cur_min = reviews.front().review.Sentiment;
        }
    }

public:
    TopN(size_t n) : count(n) { }

    // check if this Review matches the Top criteria
    void check(const Review& review) {
        if (review.review.Sentiment >= cur_min) {
            insert(review);
        }
    }

    // the current top items
    std::list<const Review>::const_iterator begin() {
        return reviews.begin();
    }

    // the end of the current top items
    std::list<const Review>::const_iterator end() {
        return reviews.end();
    }
};