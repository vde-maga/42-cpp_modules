#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <exception>
#include <algorithm>

class NotFoundException : public std::exception
{
public:
    NotFoundException();
    NotFoundException(const NotFoundException& other);
    NotFoundException& operator=(const NotFoundException& other);
    virtual ~NotFoundException() throw();

    virtual const char* what() const throw();
};

template<typename T>
typename T::iterator easyfind(T& c, int e);

template<typename T>
typename T::const_iterator easyfind(const T& c, int e);

#include "../include/Easyfind.tpp"

#endif