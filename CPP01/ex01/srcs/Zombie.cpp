#include "Colors.hpp"
#include "Zombie.hpp"
#include <iostream>

Zombie::~Zombie(void)
{
	std::cout << CYAN << "Zombie " << RESET << UNDERLINE << this->getName()
		<< RESET << RED << " died" << RESET << std::endl;
}

void Zombie::setName(std::string name)
{
	this->name = name;
}

const std::string &Zombie::getName(void) const
{
	return (this->name);
}

void Zombie::announce(void)
{
	std::cout << UNDERLINE << this->getName() << RESET << ": "
		<< GREEN << " BraiiiiiiinnnzzzZ..." << RESET << std::endl;
}
