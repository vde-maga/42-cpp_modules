#ifndef EASYFIND_TPP
#define EASYFIND_TPP

template<typename T>
typename T::iterator easyfind(T& c, int e)
{
    const typename T::iterator it = std::find(c.begin(), c.end(), e);
    if (it == c.end())
        throw NotFoundException();
    return it;
}

template<typename T>
typename T::const_iterator easyfind(const T& c, int e)
{
    const typename T::const_iterator it = std::find(c.begin(), c.end(), e);
    if (it == c.end())
        throw NotFoundException();
    return it;
}

#endif