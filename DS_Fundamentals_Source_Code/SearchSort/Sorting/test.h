#include <string>
#include <algorithm>
#include <cassert>

namespace sorting 
{

    template<class _Sort>
    std::string sort(std::string data, _Sort sortfunc)
    {
        sortfunc(data.begin(), data.end());
        return data;
    }

    template<class _Compare>
    bool sorted(std::string data, _Compare compare)
    {
        return std::is_sorted(data.begin(), data.end(), compare);
    }

    template<class _Sort, class _Compare>
    void test(std::string data, _Sort sortfunc, _Compare compare)
    {
        data = sorting::sort(data, sortfunc);
        assert(sorted(data, compare));
    }
}