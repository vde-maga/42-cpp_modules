#include "Colors.hpp"
#include "Weapon.hpp"
#include <iostream>

Weapon::Weapon(const std::string &type) : _type(type)
{
	std::cout << BLUE << "Weapon " << RESET
		<< UNDERLINE << this->_type << RESET
		<< GREEN << " forged!" << RESET << std::endl;
}

Weapon::~Weapon(void)
{
	std::cout << BLUE << "Weapon " << RESET
		<< UNDERLINE << this->_type << RESET
		<< RED << " destroyed!" << RESET << std::endl;
}

const std::string &Weapon::getType(void) const
{
	return (this->_type);
}

void Weapon::setType(const std::string &type)
{
	this->_type = type;
}
