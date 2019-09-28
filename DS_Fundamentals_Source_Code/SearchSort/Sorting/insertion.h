#include <algorithm>
#include <iterator> 

namespace sorting
{
    template<class _Iter>
    void insertion(_Iter first, _Iter last)
    {
        insertion(
            first,
            last,
            std::less<std::iterator_traits<_Iter>::value_type>()
            );
    }

    template<class _Iter, class _Compare>
    void insertion(_Iter first, _Iter last, _Compare compare) 
    {
        for (_Iter cur = first; cur < last; cur++) {
            _Iter scan = cur + 1;
            
            while (--scan != first 
                   && compare(*scan, *(scan - 1)))
            {
                std::iter_swap(scan, scan - 1);
            }
        }
    }
}