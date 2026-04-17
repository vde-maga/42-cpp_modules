#include "Zombie.hpp"
#include <string>

Zombie	*zombieHorde(int n, std::string name)
{
	Zombie	*zombieArray;

	zombieArray = new Zombie[n];
	for (int i = 0; i < n; ++i)
		zombieArray[i].setName(name);
	return (zombieArray);
}
