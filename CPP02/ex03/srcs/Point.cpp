#include "Point.hpp"

Point::Point() : _x(Fixed()), _y(Fixed())
{
}

Point::Point(Fixed const &x, Fixed const &y) : _x(x), _y(y)
{
}

Point::Point(Point const &other) : _x(other._x), _y(other._y)
{
}

Point &Point::operator=(Point const &other)
{
	(void)other;
	return (*this);
}

Point::~Point()
{
}

Fixed const &Point::getX(void) const
{
	return (_x);
}

Fixed const &Point::getY(void) const
{
	return (_y);
}
