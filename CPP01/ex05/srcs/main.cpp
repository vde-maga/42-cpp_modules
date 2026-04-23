#include "Harl.hpp"
#include "Colors.hpp"
#include <iostream>

void	run_test(const Harl &harl, const std::string &level)
{
	std::cout << MAGENTA << "[ Testing level: \"" << level << "\" ]"
				<< RESET << std::endl;
	harl.complain(level);
	std::cout << std::endl;
}

int	main(void)
{
	Harl	harl;

	run_test(harl, "DEBUG");
	run_test(harl, "INFO");
	run_test(harl, "WARNING");
	run_test(harl, "ERROR");


	run_test(harl, "INVALID_LEVEL");
	run_test(harl, "");


	run_test(harl, "debug");


	std::cout << MAGENTA << "Testing Direto - Gaming" << RESET << std::endl;
	harl.complain("Gaming");
	std::cout << MAGENTA << "Testing Direto - DEBUG" << RESET << std::endl;
	harl.complain("DEBUG");
	return (0);
}
