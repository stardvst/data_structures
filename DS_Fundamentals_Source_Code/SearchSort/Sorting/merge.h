#include <algorithm>
#include <iterator> 
#include <vector>

namespace sorting
{
    template<class _Iter>
    void merge(_Iter first, _Iter last)
    {
        merge(
            first,
            last,
            std::less<std::iterator_traits<_Iter>::value_type>()
            );
    }

    template<class _Iter, class _Compare>
    void merge(_Iter first, _Iter last, _Compare compare)
    {
        if (first == last || first+1 == last) {
            // the range is empty or a single value
            return;
        }
        
        _Iter middle = first + (last - first) / 2;

        // middle will not be in the sorted range
        merge(first, middle, compare);

        // middle will be in the sorted range
        merge(middle, last, compare);

        join(first, middle, last, compare);
    }

    template<class _Iter, class _Compare>
    void join(_Iter first, _Iter middle, _Iter last,
              _Compare compare) {
        _Iter left = first;
        _Iter right = middle;

        std::vector<std::iterator_traits<_Iter>::value_type> merged;

        // while there is data to process
        while (true)
        {
            // if we are out of left
            if (left == middle) {
                // add the rest of right
                merged.insert(merged.end(), right, last);
                break;
            }
            
            // if we're out of right
            if (right == last) {
                // add the rest of left
                merged.insert(merged.end(), left, middle);
                break;
            }
            
            // pick the lessor value
            if (compare(*left, *right)) {
                merged.push_back(*left);
                left++;
            }
            else {
                merged.push_back(*right);
                right++;
            }
        }

        // now copy the values back
        left = first;
        for (size_t i = 0; i < merged.size(); i++) {
            *left = merged[i];
            left++;
        }
    }
}
