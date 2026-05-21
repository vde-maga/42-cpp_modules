#include "Colors.hpp"
#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string &name) : _name(name), _weapon(NULL)
{
}

void HumanB::setWeapon(Weapon &weapon)
{
	this->_weapon = &weapon;
}

void HumanB::attack(void) const
{
	if (this->_weapon)
	{
		std::cout << BRIGHT_CYAN << this->_name << RESET
			<< BOLD << " attacks with their " << RESET
			<< BRIGHT_YELLOW << this->_weapon->getType() << RESET << std::endl;
	}
	else
	{
		std::cout << BRIGHT_CYAN << this->_name << RESET
			<< RED << " tries to attack but has no weapon!" << RESET << std::endl;
	}
}
