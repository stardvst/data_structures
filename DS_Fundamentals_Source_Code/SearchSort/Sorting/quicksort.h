#include <algorithm>
#include <iterator> 

namespace sorting
{
    template<class _Iter, class _Compare>
    _Iter pick_pivot(_Iter start, _Iter end, _Compare compare)
    {
        _Iter first = start;
        _Iter middle = start + (end - start) / 2;
        _Iter last = end - 1;

        _Iter trueMiddle = compare(*first, *middle)
            ? (compare(*middle, *last) ? middle : (compare(*first, *last) ? last : first))
            : (compare(*first, *last) ? first : (compare(*middle, *last) ? last : middle));

        return trueMiddle;
    }

    template<class _Iter, class _Compare>
    _Iter part(_Iter start, _Iter end, _Compare compare)
    {
        //pick our pivot point
        _Iter pivot = pick_pivot(start, end, compare);

        auto val = *pivot;

        // skip any items that are already on the correct side
        while (start != end && compare(*start, val))
        {
            ++start;
        }

        // if we made it to the end, we're done
        if (start == end)
        {
            return (start);
        }

        // move values to the correct side of the pivot
        for (_Iter next = std::next(start); next != end; ++next)
        {
            if (compare(*next, val))
            {
                std::iter_swap(start++, next);
            }
        }

        // find the correct iterator to return (the pivot)
        if (*start != val)
        {
            for (int i = 0; i < (end - start); i++)
            {
                if (*(start + i) == val)
                {
                    std::iter_swap(start, start + i);
                }
            }
        }
        return (start);
    }

    template<class _Iter>
    void quicksort(_Iter first, _Iter last)
    {
        quicksort(
            first,
            last,
            std::less<std::iterator_traits<_Iter>::value_type>()
            );
    }

    template<class _Iter, class _Compare>
    void quicksort(_Iter start, _Iter end, _Compare compare)
    {
        if ((end - start) > 1)
        {
            _Iter pivot = part(start, end, compare);

            quicksort(start, pivot, compare);
            quicksort(pivot + 1, end, compare);
        }
    }
}