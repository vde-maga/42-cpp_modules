#include "Zombie.hpp"
#include "Colors.hpp"
#include <iostream>


Zombie::~Zombie(void)
{
	std::cout << "Zombie " << this->getName() << RED <<" died" << RESET << std::endl;
}

void	Zombie::setName(std::string name)
{
	this->name = name;
}

const std::string&	Zombie::getName(void) const
{
	return (this->name);
}

void	Zombie::announce( void )
{
	std::cout << this->getName() << ": " << GREEN << " BraiiiiiiinnnzzzZ..." << RESET << std::endl;
}
