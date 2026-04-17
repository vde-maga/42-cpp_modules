#include "Colors.hpp"
#include "Zombie.hpp"
#include <cstdio>
#include <iostream>

void	randomChump(std::string name);
Zombie	*newZombie(std::string name);

int	main(void)
{
	Zombie	*z;

	std::string input;
	std::cout << MAGENTA << "Stack Zombie Name: " << RESET;
	getline(std::cin, input);
	if (std::cin.eof())
	{
		std::cin.clear();
		clearerr(stdin);
		std::cout << std::endl;
	}
	randomChump(input);
	std::cout << CYAN << "Heap Zombie Name: " << RESET;
	getline(std::cin, input);
	if (std::cin.eof())
	{
		std::cin.clear();
		clearerr(stdin);
		std::cout << std::endl;
	}
	z = newZombie(input);
	z->announce();
	delete (z);
	return (0);
}
