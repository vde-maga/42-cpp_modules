#include "Colors.hpp"
#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(void) : _name("Lara")
{
}

Zombie::~Zombie(void)
{
	std::cout << CYAN << "Zombie " << RESET
		<< UNDERLINE << this->getName() << RESET
		<< RED << " died" << RESET << std::endl;
}

void Zombie::setName(const std::string &name)
{
	this->_name = name;
}

const std::string &Zombie::getName(void) const
{
	return (this->_name);
}

void Zombie::announce(void) const
{
	std::cout << UNDERLINE << this->getName() << RESET << ": "
		<< GREEN << "BraiiiiiiinnnzzzZ..." << RESET << std::endl;
}
