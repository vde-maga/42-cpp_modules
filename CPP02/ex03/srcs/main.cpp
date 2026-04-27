#include "Point.hpp"
#include <iostream>
#include <cassert>

void	testBsp(void)
{
	Point	a(Fixed(0), Fixed(0));
	Point	b(Fixed(10), Fixed(0));
	Point	c(Fixed(0), Fixed(10));
	
	Point	inside(Fixed(1), Fixed(1));
	Point	outside(Fixed(10), Fixed(10));
	Point	on_edge(Fixed(5), Fixed(0));
	Point	on_vertex(Fixed(0), Fixed(0));

	std::cout << "Point (1, 1) inside triangle (0,0)-(10,0)-(0,10): " 
		<< (bsp(a, b, c, inside) ? "True" : "False") << std::endl;
	std::cout << "Point (10, 10) inside triangle (0,0)-(10,0)-(0,10): " 
		<< (bsp(a, b, c, outside) ? "True" : "False") << std::endl;
	std::cout << "Point (5, 0) on edge triangle (0,0)-(10,0)-(0,10): " 
		<< (bsp(a, b, c, on_edge) ? "True" : "False") << std::endl;
	std::cout << "Point (0, 0) on vertex triangle (0,0)-(10,0)-(0,10): " 
		<< (bsp(a, b, c, on_vertex) ? "True" : "False") << std::endl;

	assert(bsp(a, b, c, inside) == true);
	assert(bsp(a, b, c, outside) == false);
	assert(bsp(a, b, c, on_edge) == false);
	assert(bsp(a, b, c, on_vertex) == false);

	Point	a2(Fixed(-5), Fixed(-5));
	Point	b2(Fixed(5), Fixed(-5));
	Point	c2(Fixed(0), Fixed(5));

	Point	inside2(Fixed(0), Fixed(0));
	Point	outside2(Fixed(-10), Fixed(-10));

	std::cout << "Point (0, 0) inside triangle (-5,-5)-(5,-5)-(0,5): " 
		<< (bsp(a2, b2, c2, inside2) ? "True" : "False") << std::endl;
	std::cout << "Point (-10, -10) inside triangle (-5,-5)-(5,-5)-(0,5): " 
		<< (bsp(a2, b2, c2, outside2) ? "True" : "False") << std::endl;

	assert(bsp(a2, b2, c2, inside2) == true);
	assert(bsp(a2, b2, c2, outside2) == false);

	std::cout << "All BSP tests passed successfully." << std::endl;
}

int	main(void)
{
	testBsp();
	return (0);
}
