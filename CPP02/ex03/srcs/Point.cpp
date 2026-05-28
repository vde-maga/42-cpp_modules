#include "Colors.hpp"
#include "Point.hpp"

Point::Point() : _x(Fixed()), _y(Fixed())
{
}

Point::Point(const float x, const float y) : _x(Fixed(x)), _y(Fixed(y))
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
