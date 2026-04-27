#include "Fixed.hpp"
#include <iostream>

void	testSubjectMain(void)
{
	Fixed	a;

	Fixed const b(10);
	Fixed const c(42.42f);
	Fixed const d(b);
	a = Fixed(1234.4321f);
	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;
	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
}

void	testConversions(void)
{
	bool	pass;
	Fixed	zero;

	pass = true;
	if (zero.toInt() != 0 || zero.toFloat() != 0.0f)
		pass = false;
	Fixed posInt(42);
	if (posInt.toInt() != 42 || posInt.toFloat() != 42.0f)
		pass = false;
	Fixed negInt(-10);
	if (negInt.toInt() != -10 || negInt.toFloat() != -10.0f)
		pass = false;
	Fixed posFloat(3.14159f);
	if (posFloat.toInt() != 3)
		pass = false;
	Fixed negFloat(-2.718f);
	if (negFloat.toInt() != -2)
		pass = false;
	std::cout << "Conversion tests: " << (pass ? "PASSED" : "FAILED") << std::endl;
}

int	main(void)
{
	testSubjectMain();
	std::cout << std::endl;
	std::cout << "---" << std::endl;
	std::cout << std::endl;
	testConversions();
	return (0);
}
