#include <algorithm>
#include <iterator> 

namespace sorting
{
    template<class _Iter>
    void bubble(_Iter first, _Iter last)
    {
        bubble(
            first,
            last,
            std::less<std::iterator_traits<_Iter>::value_type>()
            );
    }

    template<class _Iter, class _Compare>
    void bubble(_Iter first, _Iter last, _Compare compare)
    {
        bool swapped;
        do
        {
            swapped = false;
            for (_Iter cur = first + 1; cur < last; cur++)
            {
                if (compare(*cur, *(cur - 1)))
                {
                    std::iter_swap(cur, cur - 1);
                    swapped = true;
                }
            }
        } while (swapped != false);
    }
}
