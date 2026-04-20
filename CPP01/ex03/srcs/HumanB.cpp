#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string &name) : _name(name), _weapon(NULL)
{
}

void HumanB::setWeapon(Weapon &weapon)
{
	// Recebemos por referência para garantir que o chamador não passa NULL diretamente aqui,
	// mas armazenamos o endereço para permitir a semântica de "opcional" na classe.
	this->_weapon = &weapon;
}

void HumanB::attack(void) const
{
	// Error handling defensivo: Presuma falhas. O ponteiro pode ser NULL.
	if (this->_weapon)
	{
		std::cout << this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
	}
	else
	{
		std::cout << this->_name << " tries to attack but has no weapon!" << std::endl;
	}
}
