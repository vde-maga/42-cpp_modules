#include "Colors.hpp"
#include "Fixed.hpp"
#include <cmath>
#include <iostream>

const int Fixed::_fractionalBits = 8;

Fixed::Fixed() : _value(0)
{
	std::cout << GREEN << "Default constructor called" << RESET << std::endl;
}

Fixed::Fixed(const int value) :
	_value(value * (1 << _fractionalBits))
{
	std::cout << RED << "Int constructor called" << RESET << std::endl;
}

Fixed::Fixed(const float value) :
	_value(static_cast<int>(roundf(value * (1 << _fractionalBits))))
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

// ======================== Comparison operators ===============================

bool Fixed::operator>(const Fixed &other) const
{
	return (_value > other._value);
}
bool Fixed::operator<(const Fixed &other) const
{
	return (_value < other._value);
}
bool Fixed::operator>=(const Fixed &other) const
{
	return (_value >= other._value);
}
bool Fixed::operator<=(const Fixed &other) const
{
	return (_value <= other._value);
}
bool Fixed::operator==(const Fixed &other) const
{
	return (_value == other._value);
}
bool Fixed::operator!=(const Fixed &other) const
{
	return (_value != other._value);
}

// ======================== Arithmetic operators ===============================

Fixed Fixed::operator+(const Fixed &other) const
{
	Fixed result;
	result.setRawBits(_value + other._value);
	return (result);
}

Fixed Fixed::operator-(const Fixed &other) const
{
	Fixed result;
	result.setRawBits(_value - other._value);
	return (result);
}

Fixed Fixed::operator*(const Fixed &other) const
{
	Fixed result;
	result.setRawBits((static_cast<long long>(_value)
			* static_cast<long long>(other._value)) >> _fractionalBits);
	return (result);
}

Fixed Fixed::operator/(const Fixed &other) const
{
	if (other._value == 0)
	{
		std::cerr << RED << "Error: Division by zero" << RESET << std::endl;
		return (Fixed());
	}
	Fixed result;
	result.setRawBits((static_cast<long long>(_value) << _fractionalBits)
		/ static_cast<long long>(other._value));
	return (result);
}

// ======================== Increment Decrement ================================
// Pre-increment (++a)
Fixed &Fixed::operator++(void)
{
	++_value;
	return (*this);
}

// Post-increment (a++)
Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	++_value;
	return (temp);
}

// Pre-decrement (--a)
Fixed &Fixed::operator--(void)
{
	--_value;
	return (*this);
}

// Post-decrement (a--)
Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	--_value;
	return (temp);
}

// ======================== Min Max ============================================
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return ((a < b) ? a : b);
}
const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return ((a < b) ? a : b);
}
Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return ((a > b) ? a : b);
}
const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return ((a > b) ? a : b);
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return (os);
}
