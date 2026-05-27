#include "Fixed.hpp"
#include "Colors.hpp"
#include <iostream>

int main(void)
{
	bool all_passed = true;

	std::cout << CYAN << "================================================" << RESET << std::endl;
	std::cout << CYAN << "   SUBJECT'S PROVIDED TEST (Mandatory Output)" << RESET << std::endl;
	std::cout << CYAN << "================================================" << RESET << std::endl;

	{
		Fixed a;
		Fixed const b(Fixed(5.05f) * Fixed(2));

		std::cout << "a is " << a << std::endl;
		std::cout << "++a is " << ++a << std::endl;
		std::cout << "a is " << a << std::endl;
		std::cout << "a++ is " << a++ << std::endl;
		std::cout << "a is " << a << std::endl;
		std::cout << "b is " << b << std::endl;
		std::cout << "max(a, b) is " << Fixed::max(a, b) << std::endl;
	}

	std::cout << std::endl;
	std::cout << BRIGHT_CYAN << "================================================" << RESET << std::endl;
	std::cout << BRIGHT_CYAN << "   UNIT TESTS: VISUAL OPERATORS & MIN/MAX" << RESET << std::endl;
	std::cout << BRIGHT_CYAN << "================================================" << RESET << std::endl;

	// Test 1: Comparison Operators
	{
		std::cout << std::endl
				  << MAGENTA << "Test 1: Comparison Operators..." << RESET << std::endl;
		Fixed a(10.5f);
		Fixed b(5.25f);
		Fixed c(10.5f);
		bool passed = true;

		std::cout << "  Comparing " << BRIGHT_YELLOW << a << RESET
				  << " and " << BRIGHT_YELLOW << b << RESET << ":" << std::endl;
		std::cout << "    " << a << " >  " << b << " : " << (a > b ? BRIGHT_GREEN "true" : BRIGHT_RED "false") << RESET << std::endl;
		std::cout << "    " << a << " <  " << b << " : " << (a < b ? BRIGHT_GREEN "true" : BRIGHT_RED "false") << RESET << std::endl;
		std::cout << "    " << a << " >= " << c << " : " << (a >= c ? BRIGHT_GREEN "true" : BRIGHT_RED "false") << RESET << std::endl;
		std::cout << "    " << a << " <= " << c << " : " << (a <= c ? BRIGHT_GREEN "true" : BRIGHT_RED "false") << RESET << std::endl;
		std::cout << "    " << a << " == " << c << " : " << (a == c ? BRIGHT_GREEN "true" : BRIGHT_RED "false") << RESET << std::endl;
		std::cout << "    " << a << " != " << b << " : " << (a != b ? BRIGHT_GREEN "true" : BRIGHT_RED "false") << RESET << std::endl;

		if (!(a > b) || !(a >= c) || !(b < a) || !(b <= a) || !(a == c) || !(a != b))
		{
			std::cerr << RED << "  -> FAIL: Comparison logic broken!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	// Test 2: Arithmetic Operators
	{
		std::cout << std::endl
				  << MAGENTA << "Test 2: Arithmetic Operators..." << RESET << std::endl;
		Fixed a(10.5f);
		Fixed b(5.25f);
		bool passed = true;

		Fixed sum = a + b;
		Fixed diff = a - b;
		Fixed prod = a * b;
		Fixed quot = a / b;

		std::cout << "  Operating " << BRIGHT_YELLOW << a << RESET
				  << " and " << BRIGHT_YELLOW << b << RESET << ":" << std::endl;
		std::cout << "    " << a << " + " << b << " = " << BRIGHT_GREEN << sum << RESET << std::endl;
		std::cout << "    " << a << " - " << b << " = " << BRIGHT_GREEN << diff << RESET << std::endl;
		std::cout << "    " << a << " * " << b << " = " << BRIGHT_GREEN << prod << RESET << std::endl;
		std::cout << "    " << a << " / " << b << " = " << BRIGHT_GREEN << quot << RESET << std::endl;

		// Validação invisible ao utilizador, mas necessária para o PASS/FAIL rigoroso (compara Raw Bits)
		if (sum.getRawBits() != (a.getRawBits() + b.getRawBits()) ||
			diff.getRawBits() != (a.getRawBits() - b.getRawBits()) ||
			prod.getRawBits() != 14112 || // 10.5 * 5.25 = 55.125 -> Raw 14112
			quot.getRawBits() != 512)	  // 10.5 / 5.25 = 2.0 -> Raw 512
		{
			std::cerr << RED << "  -> FAIL: Arithmetic precision mismatch!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	// Test 3: Increment / Decrement (Epsilon)
	{
		std::cout << std::endl
				  << MAGENTA << "Test 3: Increment & Decrement (Epsilon = 1/256)..." << RESET << std::endl;
		Fixed a(0.0f);
		bool passed = true;

		std::cout << "  Initial value: " << BRIGHT_YELLOW << a << RESET << std::endl;

		Fixed pre_inc = ++a;
		std::cout << "  After ++a:     " << BRIGHT_GREEN << a << RESET
				  << " (Pre-inc returned: " << pre_inc << ")" << std::endl;

		Fixed post_inc = a++;
		std::cout << "  After a++:     " << BRIGHT_GREEN << a << RESET
				  << " (Post-inc returned: " << post_inc << ")" << std::endl;

		Fixed pre_dec = --a;
		std::cout << "  After --a:     " << BRIGHT_GREEN << a << RESET
				  << " (Pre-dec returned: " << pre_dec << ")" << std::endl;

		Fixed post_dec = a--;
		std::cout << "  After a--:     " << BRIGHT_GREEN << a << RESET
				  << " (Post-dec returned: " << post_dec << ")" << std::endl;

		// a voltou a 0 por causa do post_dec. Verificamos os raw bits do ponto mais alto (2)
		if (a.getRawBits() != 0 || pre_inc.getRawBits() != 1 || post_inc.getRawBits() != 1 || a.getRawBits() != 0)
		{
			std::cerr << RED << "  -> FAIL: Increment/Decrement logic broken!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	// Test 4: Min / Max
	{
		std::cout << std::endl
				  << MAGENTA << "Test 4: Min & Max Functions..." << RESET << std::endl;
		Fixed a(42.42f);
		Fixed b(-10.5f);
		const Fixed c(100.0f);
		const Fixed d(0.5f);
		bool passed = true;

		std::cout << "  Non-const: " << BRIGHT_YELLOW << a << RESET << " and " << BRIGHT_YELLOW << b << RESET << std::endl;
		std::cout << "    min(a, b) = " << BRIGHT_GREEN << Fixed::min(a, b) << RESET << std::endl;
		std::cout << "    max(a, b) = " << BRIGHT_GREEN << Fixed::max(a, b) << RESET << std::endl;

		std::cout << "  Const:     " << BRIGHT_YELLOW << c << RESET << " and " << BRIGHT_YELLOW << d << RESET << std::endl;
		std::cout << "    min(c, d) = " << BRIGHT_GREEN << Fixed::min(c, d) << RESET << std::endl;
		std::cout << "    max(c, d) = " << BRIGHT_GREEN << Fixed::max(c, d) << RESET << std::endl;

		if (&Fixed::min(a, b) != &b || &Fixed::max(a, b) != &a ||
			&Fixed::min(c, d) != &d || &Fixed::max(c, d) != &c)
		{
			std::cerr << RED << "  -> FAIL: Min/Max returned wrong reference!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	// Test 5: Division by Zero (Defensive)
	{
		std::cout << std::endl
				  << MAGENTA << "Test 5: Division by Zero..." << RESET << std::endl;
		Fixed a(10.0f);
		Fixed zero(0.0f);
		bool passed = true;

		std::cout << "  Attempting " << BRIGHT_YELLOW << a << " / " << zero << RESET << std::endl;
		Fixed result = a / zero; // Should print Error message from Fixed.cpp
		std::cout << "  Result returned: " << BRIGHT_YELLOW << result << RESET << " (Should fallback to 0)" << std::endl;

		if (result.getRawBits() != 0)
		{
			std::cerr << RED << "  -> FAIL: Division by zero did not return 0!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	std::cout << std::endl
			  << BRIGHT_CYAN << "================================================" << RESET << std::endl;
	if (all_passed)
		std::cout << BRIGHT_GREEN << "   All Fixed Operator tests passed!" << RESET << std::endl;
	else
		std::cout << BRIGHT_RED << "   Some Fixed Operator tests failed." << RESET << std::endl;
	std::cout << BRIGHT_CYAN << "================================================" << RESET << std::endl;

	return (all_passed ? 0 : 1);
}