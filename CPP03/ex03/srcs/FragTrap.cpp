#include "Colors.hpp"
#include "FragTrap.hpp"
#include <iostream>

// ---------------------- Orthodox Canonical Form ------------------------------

FragTrap::FragTrap(void) : ClapTrap()
{
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;

	std::cout << GREEN UNDERLINE << "FragTrap " << _name
		<< " default constructor called"
		<< RESET << std::endl;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name)
{
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;


	std::cout << GREEN UNDERLINE << "FragTrap " << _name
		<< " parameterized constructor called"
		<< RESET << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other)
{
	std::cout << GREEN UNDERLINE << "FragTrap " << _name
		<< " copy constructor called"
		<< RESET << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
	std::cout << GREEN UNDERLINE << "FragTrap " << _name
		<< " assigment operator called"
		<< RESET << std::endl;

	if (this != &other)
		ClapTrap::operator=(other);
	return (*this);
}

FragTrap::~FragTrap(void)
{
	std::cout << GREEN UNDERLINE << "FragTrap " << _name
		<< " destructor called"
		<< RESET << std::endl;
}

// ---------------------- Public Methods ---------------------------------------

void FragTrap::attack(const std::string &target)
{
	if (_hitPoints == 0 || _energyPoints == 0)
	{
		std::cout << "FragTrap " << _name
			<< CYAN << " cannot attack!"
			<< RESET << std::endl;
		return ;
	}

	--_energyPoints;

	std::cout << "FragTrap " << _name
		<< RED << " attacks " << RESET << target
		<< ", causing " << _attackDamage << " points of damage!"
		<< RESET << std::endl;
}

void FragTrap::highFivesGuys(void) const
{
	std::cout << "FragTrap " << _name
		<< MAGENTA << " requests a positive high-fives!"
		<< RESET << std::endl;
}
