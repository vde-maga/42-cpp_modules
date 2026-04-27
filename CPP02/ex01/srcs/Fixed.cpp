#include "Colors.hpp"
#include "Fixed.hpp"
#include <cmath>
#include <iostream>

Fixed::Fixed() : _value(0)
{
	std::cout << GREEN << "Default constructor called" << RESET << std::endl;
}

Fixed::Fixed(const int value) : _value(value * (1 << _fractionalBits))
{
	std::cout << RED << "Int constructor called" << RESET << std::endl;
}

Fixed::Fixed(const float value) : _value(static_cast<int>(roundf(value
			* (1 << _fractionalBits))))
{
	std::cout << WHITE << "Float constructor called" << RESET << std::endl;
}

Fixed::Fixed(const Fixed &other) : _value(other._value)
{
	std::cout << YELLOW << "Copy constructor called" << RESET << std::endl;
}

Fixed &Fixed::operator=(const Fixed &other)
{
	std::cout << BLUE << "Copy assignment operator called" << RESET << std::endl;
	if (this != &other)
		_value = other._value;
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << MAGENTA << "Destructor called" << RESET << std::endl;
}

int Fixed::getRawBits(void) const
{
	std::cout << CYAN << "getRawBits member function called" << RESET << std::endl;
	return (_value);
}

void Fixed::setRawBits(int const raw)
{
	_value = raw;
}

float Fixed::toFloat(void) const
{
	return (static_cast<float>(_value) / (1 << _fractionalBits));
}

int Fixed::toInt(void) const
{
	return (_value / (1 << _fractionalBits));
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return (os);
}
