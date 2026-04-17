#include "Colors.hpp"
#include "Zombie.hpp"
#include <cstdio>
#include <iostream>

Zombie	*zombieHorde(int n, std::string name);

int	main(void)
{
	int		nZombies;
	Zombie	*zombiesHorde;

	std::string zombiesName;
	while (true)
	{
		std::cout << MAGENTA << "Zombies Names?: " << RESET;
		getline(std::cin, zombiesName);
		if (std::cin.eof())
		{
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
		}
		if (!zombiesName.empty())
			break ;
		std::cout << YELLOW << "Please insert a valid name for the Zombies"
			<< RESET << std::endl;
	}
	std::cout << MAGENTA << "How many Zombies?: " << RESET;
	std::cin >> nZombies;
	if (nZombies < 0)
	{
		std::cout << RED << "Cant have negative Zombies"
			<< RESET << std::endl;
		return (1);
	}
	zombiesHorde = zombieHorde(nZombies, zombiesName);
	for (int i = 0; i < nZombies; ++i)
		zombiesHorde[i].announce();
	delete[](zombiesHorde);
	return (0);
}
