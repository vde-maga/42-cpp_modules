#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string name, Weapon &weapon) : _name(name), _weapon(weapon)
{
}

void	HumanA::attack(void)
{
	std::cout << this->_name << " attacks with their " << this->weapon.getType() << std::endl;
}
