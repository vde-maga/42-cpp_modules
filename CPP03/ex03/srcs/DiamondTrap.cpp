#include "DiamondTrap.hpp"
#include "Colors.hpp"
#include <iostream>

// ---------------------- Orthodox Canonical Form ------------------------------

// Na herança virtual, a classe mais derivada (DiamondTrap) é QUEM inicializa a base virtual (ClapTrap)
DiamondTrap::DiamondTrap(void) :
	ClapTrap("Default_clap_name"), ScavTrap(), FragTrap(),
	_name("Default")
{
	// Os construtores de Scav e Frag vão correr e alterar estes valores.
	// Como a ordem de execução dos corpos é Scav -> Frag -> Diamond,
	// os valores de Frag sobrepunham-se. Redefinimos aqui para garantir o estado final correto.
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 30;

	std::cout << GREEN UNDERLINE << "DiamondTrap " << _name
		<< " default constructor called"
		<< RESET << std::endl;
}

DiamondTrap::DiamondTrap(const std::string &name) :
	ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name),
	_name(name)
{
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 30;

	std::cout << GREEN UNDERLINE << "DiamondTrap " << _name
		<< " parameterized constructor called"
		<< RESET << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other) :
	ClapTrap(other), ScavTrap(other), FragTrap(other),
	_name(other._name)
{
	std::cout << GREEN UNDERLINE << "DiamondTrap " << _name
		<< " copy constructor called"
		<< RESET << std::endl;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &other)
{
	std::cout << GREEN UNDERLINE << "DiamondTrap " << _name
		<< " assigment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		ClapTrap::operator=(other);
		_name = other._name;
	}
	return (*this);
}

DiamondTrap::~DiamondTrap(void)
{
	std::cout << GREEN UNDERLINE << "DiamondTrap " << _name
		<< " destructor called"
		<< RESET << std::endl;
}

// ---------------------- Public Methods ---------------------------------------

void DiamondTrap::attack(const std::string &target)
{
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI(void) const
{
	std::cout << "DiamondTrap name: " << BRIGHT_CYAN << _name
		<< RESET << ", ClapTrap name: " << BRIGHT_YELLOW << ClapTrap::_name
		<< RESET << std::endl;
}
