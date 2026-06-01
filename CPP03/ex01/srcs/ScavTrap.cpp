#include "Colors.hpp"
#include "ScavTrap.hpp"
#include <iostream>

// ---------------------- Orthodox Canonical Form ------------------------------

ScavTrap::ScavTrap(void) : ClapTrap()
{
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;

	std::cout << GREEN UNDERLINE << "ScavTrap " << _name
		<< " default constructor called"
		<< RESET << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;

	std::cout << GREEN UNDERLINE << "ScavTrap " << _name
		<< " parameterized constructor called"
		<< RESET << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other)
{
	std::cout << GREEN UNDERLINE << "ScavTrap " << _name
		<< " copy constructor called"
		<< RESET << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other)
{
	std::cout << GREEN UNDERLINE << "ScavTrap " << _name
		<< " assigment operator called"
		<< RESET << std::endl;

	if (this != &other)
		ClapTrap::operator=(other);
	return (*this);
}

ScavTrap::~ScavTrap(void)
{
	std::cout << GREEN UNDERLINE << "ScavTrap " << _name
		<< " destructor called"
		<< RESET << std::endl;
}

// ---------------------- Public Methods ---------------------------------------

void ScavTrap::attack(const std::string &target)
{
	if (_hitPoints == 0 || _energyPoints == 0)
	{
		std::cout << "ScavTrap " << _name
			<< CYAN << " cannot attack!"
			<< RESET << std::endl;
		return ;
	}
	
	--_energyPoints;

	std::cout << "ScavTrap " << _name
		<< RED << " attacks " << RESET << target
		<< ", causing " << _attackDamage << " points of damage!"
		<< RESET << std::endl;
}

void ScavTrap::guardGate(void) const
{
	std::cout << "ScavTrap " << _name
		<< MAGENTA << " is now in Gate keeper mode!"
		<< RESET << std::endl;
}
