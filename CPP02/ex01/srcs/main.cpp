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

	std::cout << std::endl;
	std::cout << BRIGHT_CYAN << "================================================" << RESET << std::endl;
	std::cout << BRIGHT_CYAN << "   UNIT TESTS: FIXED CONVERSIONS (Destructive)" << RESET << std::endl;
	std::cout << BRIGHT_CYAN << "================================================" << RESET << std::endl;

	{
		std::cout << std::endl
				  << MAGENTA << "Test 1: Int Constructor (positive & negative)..." << RESET << std::endl;
		Fixed posInt(42);
		Fixed negInt(-10);
		bool passed = true;

		int posRaw = posInt.getRawBits(); // 42 * 256 = 10752
		std::cout << "  -> PosInt Raw: " << BRIGHT_YELLOW << posRaw << RESET
				  << " | Expected: " << BRIGHT_YELLOW << (42 * 256) << RESET << std::endl;

		int negRaw = negInt.getRawBits(); // -10 * 256 = -2560
		std::cout << "  -> NegInt Raw: " << BRIGHT_YELLOW << negRaw << RESET
				  << " | Expected: " << BRIGHT_YELLOW << (-10 * 256) << RESET << std::endl;

		if (posRaw != (42 * 256) || negRaw != (-10 * 256))
		{
			std::cerr << RED << "  -> FAIL: Int conversion mismatch!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	{
		std::cout << std::endl
				  << MAGENTA << "Test 2: Float Constructor & roundf behavior..." << RESET << std::endl;
		Fixed half(1.5f);
		Fixed negHalf(-1.5f);
		bool passed = true;

		// 1.5 * 256 = 384
		int halfRaw = half.getRawBits();
		std::cout << "  -> 1.5f Raw: " << BRIGHT_YELLOW << halfRaw << RESET
				  << " | Expected: " << BRIGHT_YELLOW << 384 << RESET << std::endl;

		// -1.5 * 256 = -384
		int negHalfRaw = negHalf.getRawBits();
		std::cout << "  -> -1.5f Raw: " << BRIGHT_YELLOW << negHalfRaw << RESET
				  << " | Expected: " << BRIGHT_YELLOW << -384 << RESET << std::endl;

		if (halfRaw != 384 || negHalfRaw != -384)
		{
			std::cerr << RED << "  -> FAIL: Float rounding/creation failed!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	{
		std::cout << std::endl
				  << MAGENTA << "Test 3: Exact Fractional Bit (1 / 256 = 0.00390625)..." << RESET << std::endl;
		Fixed tiny(0.00390625f);
		bool passed = true;

		// 0.00390625 * 256 = 1
		int tinyRaw = tiny.getRawBits();
		std::cout << "  -> Tiny Raw: " << BRIGHT_YELLOW << tinyRaw << RESET
				  << " | Expected: " << BRIGHT_YELLOW << 1 << RESET << std::endl;
		std::cout << "  -> Tiny Float: " << BRIGHT_YELLOW << tiny.toFloat() << RESET
				  << " | Expected: ~0.00390625" << RESET << std::endl;

		if (tinyRaw != 1)
		{
			std::cerr << RED << "  -> FAIL: Precision loss on exact fractional bit!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	{
		std::cout << std::endl
				  << MAGENTA << "Test 4: toInt truncates correctly (no rounding)..." << RESET << std::endl;
		Fixed f(42.42f);
		Fixed nf(-2.718f);
		bool passed = true;

		int fInt = f.toInt();
		int nfInt = nf.toInt();
		std::cout << "  -> 42.42f toInt: " << BRIGHT_YELLOW << fInt << RESET
				  << " | Expected: " << BRIGHT_YELLOW << 42 << RESET << std::endl;
		std::cout << "  -> -2.718f toInt: " << BRIGHT_YELLOW << nfInt << RESET
				  << " | Expected: " << BRIGHT_YELLOW << -2 << RESET << std::endl;

		if (fInt != 42 || nfInt != -2)
		{
			std::cerr << RED << "  -> FAIL: toInt did not truncate properly!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	{
		std::cout << std::endl
				  << MAGENTA << "Test 5: Large values (Limits check)..." << RESET << std::endl;
		Fixed big(10000); // 10000 * 256 = 2,560,000 (Safe for int)
		bool passed = true;

		int bigRaw = big.getRawBits();
		std::cout << "  -> 10000 Raw: " << BRIGHT_YELLOW << bigRaw << RESET
				  << " | Expected: " << BRIGHT_YELLOW << (10000 * 256) << RESET << std::endl;

		if (bigRaw != (10000 * 256))
		{
			std::cerr << RED << "  -> FAIL: Large integer multiplication failed!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	{
		std::cout << std::endl
				  << MAGENTA << "Test 6: Self-Assignment protection..." << RESET << std::endl;
		Fixed f(123.456f);
		Fixed &f_ref = f;
		f = f_ref;
		bool passed = true;

		int raw = f.getRawBits();
		// 123.456 * 256 = 31604.736 -> roundf -> 31605
		std::cout << "  -> Self-assigned Raw: " << BRIGHT_YELLOW << raw << RESET
				  << " | Expected: " << BRIGHT_YELLOW << 31605 << RESET << std::endl;

		if (raw != 31605)
		{
			std::cerr << RED << "  -> FAIL: Value corrupted after self-assignment!" << RESET << std::endl;
			passed = false;
			all_passed = false;
		}
		else
			std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}

	std::cout << std::endl
			  << BRIGHT_CYAN << "================================================" << RESET << std::endl;
	if (all_passed)
		std::cout << BRIGHT_GREEN << "   All Fixed Conversions tests passed!" << RESET << std::endl;
	else
		std::cout << BRIGHT_RED << "   Some Fixed Conversions tests failed." << RESET << std::endl;
	std::cout << BRIGHT_CYAN << "================================================" << RESET << std::endl;

	return (all_passed ? 0 : 1);
}
