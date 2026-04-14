#include "../includes/Colors.hpp"
#include "../includes/PhoneBook.hpp"
#include <cstdio>
#include <iostream>

// C++ idiomático: usa bool em vez de int para avaliações lógicas
bool	isInputValid(const std::string &input)
{
	return (input == "ADD" || input == "SEARCH" || input == "EXIT"
		|| input == "add" || input == "search" || input == "exit");
}

std::string getUserInput(void)
{
	std::string input;
	while (true)
	{
		std::cout << GREEN << "PhoneBook> " << RESET << std::flush;
		if (!std::getline(std::cin, input))
		{
			// Prevenção contra EOF infinito (Ctrl+D)
			if (std::cin.eof())
			{
				std::cin.clear();
				clearerr(stdin);
				std::cout << std::endl;
			}
			else
				std::cin.clear();
			continue ;
		}
		if (!input.empty() && isInputValid(input))
			break ;
		std::cout << RED << "Please insert a valid input (ADD, SEARCH, EXIT)"
			<< RESET << std::endl;
	}
	return (input);
}

int	main(void)
{
	PhoneBook phoneBook;

	std::cout << GREEN << "Phone Book" << RESET << std::endl;
	std::cout << MAGENTA << "ADD" << RESET;
	std::cout << " | ";
	std::cout << CYAN << "SEARCH" << RESET;
	std::cout << " | ";
	std::cout << RED << "EXIT" << RESET << std::endl;

	while (true)
	{
		std::string userInput = getUserInput();
		if (userInput == "ADD" || userInput == "add")
			phoneBook.addContact();
		else if (userInput == "SEARCH" || userInput == "search")
			phoneBook.searchContact();
		else if (userInput == "EXIT" || userInput == "exit")
			break ;
	}
	return (0);
}