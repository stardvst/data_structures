namespace search
{
    template<class _Iter, class _Type>
    bool binary(_Iter first, _Iter last, const _Type& val) {

        _Iter middle = first + (last - first) / 2;

        if (middle == last)
            return false;

        if ((*middle) == val)
            return true;

        // search to the left
        if ((*middle) > val)
            return binary(first, middle, val);

        // search to the right
        return binary(middle + 1, last, val);
    }

    template<class _Iter, class _Type>
    bool binary_norec(_Iter first, _Iter last, const _Type& val) {

        while (true)
        {
            _Iter middle = first + (last - first) / 2;

            if (middle == last)
                return false;

            if ((*middle) == val)
                return true;

            if ((*middle) > val)
                last = middle;      // search left
            else
                first = middle + 1; // search right
        }
    }
}