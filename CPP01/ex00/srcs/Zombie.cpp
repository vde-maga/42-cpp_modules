#include "Colors.hpp"
#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(void) : _name("Lara")
{
}

Zombie::Zombie(const std::string &name) : _name(name)
{
}

Zombie::~Zombie(void)
{
	std::cout << "Zombie " << this->getName() << RED << " died"
		<< RESET << std::endl;
}

const std::string &Zombie::getName(void) const
{
	return (this->_name);
}

void Zombie::announce(void) const
{
	std::cout << this->getName() << ": " << GREEN << "BraiiiiiiinnnzzzZ..."
		<< RESET << std::endl;
}
