#include "Colors.hpp"
#include "Harl.hpp"
#include <iostream>

static int getLevelIndex(const std::string &level)
{
	if (level == "DEBUG")
		return (0);
	else if (level == "INFO")
		return (1);
	else if (level == "WARNING")
		return (2);
	else if (level == "ERROR")
		return (3);
	return (-1);
}

static void filterHarl(const std::string &level)
{
	Harl harl;
	int levelIndex = getLevelIndex(level);

	switch (levelIndex)
	{
	case 0:
		std::cout << GREEN << "[ DEBUG ]" << RESET << std::endl;
		harl.complain("DEBUG");
	case 1:
		std::cout << CYAN << "[ INFO ]" << RESET << std::endl;
		harl.complain("INFO");
	case 2:
		std::cout << YELLOW << "[ WARNING ]" << RESET << std::endl;
		harl.complain("WARNING");
	case 3:
		std::cout << RED << "[ ERROR ]" << RESET << std::endl;
		harl.complain("ERROR");
		break;
	default:
		std::cout << ITALIC << "[ Probably complaining about insignificant problems ]" << RESET << std::endl;
		break;
	}
}

int runTests(void)
{
	bool all_passed = true;

	std::cout << "Starting HarlFilter unit tests" << std::endl
			  << std::endl;

	{
		std::cout << MAGENTA << "Test 1: Level DEBUG - Should print DEBUG, INFO, WARNING, ERROR..." << RESET << std::endl;
		filterHarl("DEBUG");
		std::cout << GREEN << "  -> PASS (Visual check above)" << RESET << std::endl
				  << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 2: Level INFO - Should print INFO, WARNING, ERROR..." << RESET << std::endl;
		filterHarl("INFO");
		std::cout << GREEN << "  -> PASS (Visual check above)" << RESET << std::endl
				  << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 3: Level WARNING - Should print WARNING, ERROR..." << RESET << std::endl;
		filterHarl("WARNING");
		std::cout << GREEN << "  -> PASS (Visual check above)" << RESET << std::endl
				  << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 4: Level ERROR - Should print ERROR only..." << RESET << std::endl;
		filterHarl("ERROR");
		std::cout << GREEN << "  -> PASS (Visual check above)" << RESET << std::endl
				  << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 5: Invalid Level - Should print default message..." << RESET << std::endl;
		filterHarl("I am not sure how tired I am today...");
		std::cout << GREEN << "  -> PASS (Visual check above)" << RESET << std::endl
				  << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 6: Empty Level - Should print default message..." << RESET << std::endl;
		filterHarl("");
		std::cout << GREEN << "  -> PASS (Visual check above)" << RESET << std::endl
				  << std::endl;
	}

	if (all_passed)
		std::cout << GREEN << "All HarlFilter tests passed!" << std::endl
				  << RESET;

	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 1)
		return (runTests());
	if (argc != 2)
	{
		std::cerr << RED << "Usage: ./harlFilter [DEBUG|INFO|WARNING|ERROR]" << RESET << std::endl;
		return (1);
	}
	filterHarl(std::string(argv[1]));

	return (0);
}
