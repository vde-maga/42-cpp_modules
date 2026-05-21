#include "Harl.hpp"
#include "Colors.hpp"
#include <iostream>

int main(void)
{
	bool all_passed = true;

	std::cout << "Starting Harl 2.0 unit tests" << std::endl
			  << std::endl;

	Harl harl;

	{
		std::cout << MAGENTA << "Test 1: Valid Levels - DEBUG, INFO, WARNING, ERROR..." << RESET << std::endl;
		bool passed = true;
		try
		{
			harl.complain("DEBUG");
			harl.complain("INFO");
			harl.complain("WARNING");
			harl.complain("ERROR");
		}
		catch (...)
		{
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
		{
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
			all_passed = false;
		}
	}

	{
		std::cout << MAGENTA << "Test 2: Invalid Levels - Case sensitivity, typos, random strings..." << RESET << std::endl;
		bool passed = true;
		try
		{
			harl.complain("debug");
			harl.complain("WARNING ");
			harl.complain("ERRORR");
			harl.complain("Gaming");
		}
		catch (...)
		{
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS (Should print [UNKNOWN] messages above)" << std::endl
					  << std::endl;
		else
		{
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
			all_passed = false;
		}
	}

	{
		std::cout << MAGENTA << "Test 3: Empty String - Should handle gracefully without crashing..." << RESET << std::endl;
		bool passed = true;
		try
		{
			harl.complain("");
		}
		catch (...)
		{
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
		{
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
			all_passed = false;
		}
	}

	{
		std::cout << MAGENTA << "Test 4: Massive String - Should not crash on huge input..." << RESET << std::endl;
		bool passed = true;
		try
		{
			std::string huge(10000, 'A');
			harl.complain(huge);
		}
		catch (...)
		{
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
		{
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
			all_passed = false;
		}
	}

	// Summary
	if (all_passed)
		std::cout << GREEN << "All Harl 2.0 tests passed!" << std::endl
				  << RESET;
	else
		std::cout << RED << "Some Harl 2.0 tests failed." << std::endl
				  << RESET;

	return (all_passed ? 0 : 1);
}
