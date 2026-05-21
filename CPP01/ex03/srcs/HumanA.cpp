#include "Colors.hpp"
#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(const std::string &name, Weapon &weapon) : _name(name),
	_weapon(weapon)
{
}

void HumanA::attack(void) const
{
	std::cout << BRIGHT_CYAN << this->_name << RESET
		<< BOLD << " attacks with their " << RESET
		<< BRIGHT_YELLOW << this->_weapon.getType() << RESET << std::endl;
}
