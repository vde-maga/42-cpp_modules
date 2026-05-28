#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
  private:
	Fixed const _x;
	Fixed const _y;

  public:
	Point();
	Point(const float x, const float y);
	Point(Point const &other);
	Point &operator=(Point const &other);
	~Point();

	Fixed const &getX(void) const;
	Fixed const &getY(void) const;
};

bool	bsp(Point const &a, Point const &b, Point const &c, Point const &point);

#endif
