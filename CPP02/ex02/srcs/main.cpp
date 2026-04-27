#include "Fixed.hpp"
#include "Colors.hpp"
#include <iostream>

void	testSubjectMain(void)
{
	Fixed	a;

	Fixed const b(Fixed(5.05f) * Fixed(2));
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max(a, b) << std::endl;
}

void	testComparisons(void)
{
	bool	pass;

	Fixed a(10.5f);
	Fixed b(5.25f);
	Fixed c(10.5f);
	pass = true;
	if (!(a > b))
		pass = false;
	if (!(a >= c))
		pass = false;
	if (!(b < a))
		pass = false;
	if (!(b <= a))
		pass = false;
	if (!(a == c))
		pass = false;
	if (!(a != b))
		pass = false;
	std::cout << "Comparison tests: " << (pass ? "PASSED" : "FAILED") << std::endl;
}

void	testArithmetic(void)
{
	bool	pass;
	Fixed	sum;
	Fixed	diff;
	Fixed	prod;
	Fixed	quot;

	Fixed a(10.5f);
	Fixed b(5.25f);
	pass = true;
	sum = a + b;
	if (sum != Fixed(15.75f))
		pass = false;
	diff = a - b;
	if (diff != Fixed(5.25f))
		pass = false;
	prod = a * b;
	if (prod != Fixed(55.125f))
		pass = false;
	quot = a / b;
	if (quot != Fixed(2.0f))
		pass = false;
	std::cout << "Arithmetic tests: " << (pass ? "PASSED" : "FAILED") << std::endl;
}

void	testMinMax(void)
{
	bool	pass;

	Fixed a(3.14f);
	Fixed b(2.71f);
	const Fixed c(-1.0f);
	const Fixed d(42.0f);
	pass = true;
	if (&Fixed::min(a, b) != &b)
		pass = false;
	if (&Fixed::max(a, b) != &a)
		pass = false;
	if (&Fixed::min(c, d) != &c)
		pass = false;
	if (&Fixed::max(c, d) != &d)
		pass = false;
	std::cout << "Min/Max tests: " << (pass ? "PASSED" : "FAILED") << std::endl;
}

int	main(void)
{
	std::cout << UNDERLINE << "Testing Subject Main" << RESET << std::endl;
	testSubjectMain();
	std::cout << std::endl;
	std::cout << "---" << std::endl;
	std::cout << std::endl;
	std::cout << UNDERLINE << "Testing Comparisons" << RESET << std::endl;
	testComparisons();
	std::cout << std::endl;
	std::cout << UNDERLINE << "Testing Arithmetic" << RESET << std::endl;
	testArithmetic();
	std::cout << std::endl;
	std::cout << UNDERLINE << "Testing Min and Max" << RESET<< std::endl;
	testMinMax();
	std::cout << std::endl;
	return (0);
}
