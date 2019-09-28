#include <algorithm>
#include <iterator> 

namespace sorting
{
    template<class _Iter>
    void selection(_Iter first, _Iter last)
    {
        selection(
            first,
            last,
            std::less<std::iterator_traits<_Iter>::value_type>()
            );
    }

    template<class _Iter, class _Compare>
    void selection(_Iter first, _Iter last, _Compare compare) {
        for (_Iter next = first; next < last; next++) {

            _Iter min = next;

            for (_Iter candidate = next; candidate < last; candidate++) {                
                if (compare(*candidate, *min)) {
                    min = candidate;
                }
            }

            if (min != next) {
                std::iter_swap(min, next);
            }
        }
    }
}