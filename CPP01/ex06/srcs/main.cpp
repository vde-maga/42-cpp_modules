#include "Colors.hpp"
#include "Harl.hpp"
#include <iostream>

static int	getLevelIndex(const std::string &level)
{
	if (level == "DEBUG")
		return (0);
	else if (level == "INFO")
		return (1);
	else if (level == "WARNING")
		return (2);
	else if (level == "ERROR")
		return (3);
	else
		return (-1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << RED << "Usage: ./harlFilter [DEBUG|INFO|WARNING|ERROR]" << RESET << std::endl;
		return (1);
	}

	const std::string input(argv[1]);
	const int	levelIndex = getLevelIndex(input);
	Harl		harl;

	switch (levelIndex)
	{
		case (0):
			std::cout << RED <<"[ DEBUG ]" << RESET << std::endl;
			harl.complain("DEBUG");
		case (1):
				std::cout << YELLOW << "[ INFO ]" << RESET << std::endl;
			harl.complain("INFO");
		case (2):
			std::cout << GREEN << "[ WARNING ]" << RESET << std::endl;
			harl.complain("WARNING");
		case (3):
			std::cout << BLUE << "[ ERROR ]" << RESET << std::endl;
			harl.complain("ERROR");
			break ;
		default:
			std::cout << ITALIC << "[ Probably complaining about insignificant problems ]"
				<< RESET << std::endl;
			break ;
	}
	return (0);
}
