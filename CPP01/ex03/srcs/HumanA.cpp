#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(const std::string &name, Weapon &weapon) : _name(name),
	_weapon(weapon)
{
	// Defensivo: O enunciado diz que HumanA SEMPRE tem arma.
	// Se alguém passar uma referência para um objeto destruído ou nulo,
	// o comportamento é indefinido, mas garantimos que a referência é obrigatória aqui.
}

void HumanA::attack(void) const
{
	// Como usamos referência, temos a garantia (pelo design da classe) de que _weapon é válido.
	std::cout << this->_name << " attacks with their " << this->_weapon.getType() << std::endl;
}
