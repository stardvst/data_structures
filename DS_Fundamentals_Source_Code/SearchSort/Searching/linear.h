namespace search
{
    template<class _Iter, class _Type>
    _Iter linear(_Iter first, _Iter last, const _Type& val)
    {
        for (; first != last; first++)
        {
            if ((*first) == val)
            {
                break;
            }
        }

        return first;
    }
}