#include "Fixed.hpp"
#include "Colors.hpp"
#include <iostream>
#include <climits>

int main(void)
{
	bool all_passed = true;

	std::cout << CYAN << "================================================" << RESET << std::endl;
	std::cout << CYAN << "   SUBJECT'S PROVIDED TEST (Mandatory Output)" << RESET << std::endl;
	std::cout << CYAN << "================================================" << RESET << std::endl;

	{
		Fixed a;
		Fixed b(a);
		Fixed c;
		c = b;
		std::cout << a.getRawBits() << std::endl;
		std::cout << b.getRawBits() << std::endl;
		std::cout << c.getRawBits() << std::endl;
	}

	std::cout << std::endl;
	std::cout << BRIGHT_CYAN << "================================================" << RESET << std::endl;
	std::cout << BRIGHT_CYAN << "   UNIT TESTS: FIXED (Automatic & Destructive)" << RESET << std::endl;
	std::cout << BRIGHT_CYAN << "================================================" << RESET << std::endl;

	{
		std::cout << std::endl
				  << MAGENTA << "Test 1: setRawBits and getRawBits normal value..." << RESET << std::endl;
		Fixed f;
		f.setRawBits(42);

		int val = f.getRawBits();
		std::cout << "  -> Returned Value: " << BRIGHT_YELLOW << val << RESET
				  << " | Expected: " << BRIGHT_YELLOW << "42" << RESET << std::endl;

		if (val != 42)
		{
			std::cerr << RED << "  -> FAIL: Mismatch!" << RESET << std::endl;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	{
		std::cout << std::endl
				  << MAGENTA << "Test 2: Self-Assignment protection..." << RESET << std::endl;
		Fixed f;
		f.setRawBits(100);

		Fixed &f_ref = f; // Bypass -Wself-assign-overloaded
		f = f_ref;		  // Triggers assignment operator

		int val = f.getRawBits();
		std::cout << "  -> Returned Value: " << BRIGHT_YELLOW << val << RESET
				  << " | Expected: " << BRIGHT_YELLOW << "100" << RESET << std::endl;

		if (val != 100)
		{
			std::cerr << RED << "  -> FAIL: Value corrupted after self-assignment!" << RESET << std::endl;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	{
		std::cout << std::endl
				  << MAGENTA << "Test 3: Extreme Values (INT_MAX / INT_MIN)..." << RESET << std::endl;
		Fixed f_max;
		Fixed f_min;
		f_max.setRawBits(INT_MAX);
		f_min.setRawBits(INT_MIN);

		int val_max = f_max.getRawBits();
		std::cout << "  -> MAX Returned: " << BRIGHT_YELLOW << val_max << RESET
				  << " | Expected: " << BRIGHT_YELLOW << INT_MAX << RESET << std::endl;

		int val_min = f_min.getRawBits();
		std::cout << "  -> MIN Returned: " << BRIGHT_YELLOW << val_min << RESET
				  << " | Expected: " << BRIGHT_YELLOW << INT_MIN << RESET << std::endl;

		if (val_max != INT_MAX || val_min != INT_MIN)
		{
			std::cerr << RED << "  -> FAIL: Extreme integer limits not handled properly!" << RESET << std::endl;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	{
		std::cout << std::endl
				  << MAGENTA << "Test 4: Copy Constructor with non-zero value..." << RESET << std::endl;
		Fixed original;
		original.setRawBits(999);
		Fixed copy(original);

		int val = copy.getRawBits();
		std::cout << "  -> Copy Value: " << BRIGHT_YELLOW << val << RESET
				  << " | Expected: " << BRIGHT_YELLOW << "999" << RESET << std::endl;

		if (val != 999)
		{
			std::cerr << RED << "  -> FAIL: Copy did not preserve value!" << RESET << std::endl;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	{
		std::cout << std::endl
				  << MAGENTA << "Test 5: Assignment Operator with non-zero value..." << RESET << std::endl;
		Fixed src;
		src.setRawBits(1234);
		Fixed dest;
		dest = src;

		int val = dest.getRawBits();
		std::cout << "  -> Dest Value: " << BRIGHT_YELLOW << val << RESET
				  << " | Expected: " << BRIGHT_YELLOW << "1234" << RESET << std::endl;

		if (val != 1234)
		{
			std::cerr << RED << "  -> FAIL: Assignment did not preserve value!" << RESET << std::endl;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	{
		std::cout << std::endl
				  << MAGENTA << "Test 6: Chained Assignment (a = b = c)..." << RESET << std::endl;
		Fixed a, b, c;
		a.setRawBits(777);
		b = c = a;

		int val_b = b.getRawBits();
		int val_c = c.getRawBits();
		std::cout << "  -> B Value: " << BRIGHT_YELLOW << val_b << RESET
				  << " | C Value: " << BRIGHT_YELLOW << val_c << RESET
				  << " | Expected: " << BRIGHT_YELLOW << "777" << RESET << std::endl;

		if (val_b != 777 || val_c != 777)
		{
			std::cerr << RED << "  -> FAIL: Chained assignment failed!" << RESET << std::endl;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	std::cout << std::endl
			  << BRIGHT_CYAN << "================================================" << RESET << std::endl;
	if (all_passed)
		std::cout << BRIGHT_GREEN << "   All Fixed tests passed!" << RESET << std::endl;
	else
		std::cout << BRIGHT_RED << "   Some Fixed tests failed." << RESET << std::endl;
	std::cout << BRIGHT_CYAN << "================================================" << RESET << std::endl;

	return (all_passed ? 0 : 1);
}
