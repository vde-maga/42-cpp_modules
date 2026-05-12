#include "ScavTrap.hpp"
#include "Colors.hpp"
#include <iostream>

// ---------------------- Orthodox Canonical Form ------------------------------

ScavTrap::ScavTrap(void) : ClapTrap()
{
	hitPoints_ = 100;
	energyPoints_ = 50;
	attackDamage_ = 20;
	std::cout << GREEN UNDERLINE << "ScavTrap " << name_
			  << " default constructor called" << RESET << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
	hitPoints_ = 100;
	energyPoints_ = 50;
	attackDamage_ = 20;
	std::cout << GREEN UNDERLINE << "ScavTrap " << name_
			  << " parameterized constructor called" << RESET << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other)
{
	std::cout << GREEN UNDERLINE << "ScavTrap " << name_
			  << " copy constructor called" << RESET << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other)
{
	std::cout << GREEN UNDERLINE << "ScavTrap " << name_
			  << " assigment operator called" << RESET << std::endl;
	if (this != &other)
		ClapTrap::operator=(other);
	return (*this);
}

ScavTrap::~ScavTrap(void)
{
	std::cout << GREEN UNDERLINE << "ScavTrap " << name_
			  << " destructor called" << RESET << std::endl;
}

// ---------------------- Public Methods ---------------------------------------

void ScavTrap::attack(const std::string &target)
{
	if (hitPoints_ == 0 || energyPoints_ == 0)
	{
		std::cout << "ScavTrap " << name_ << CYAN << " cannot attack!"
				  << RESET << std::endl;
		return;
	}
	energyPoints_--;
	std::cout << "ScavTrap " << name_ << RED << " attacks " << RESET << target
			  << ", causing " << attackDamage_ << " points of damage!" << std::endl;
}

void ScavTrap::guardGate(void)
{
	std::cout << "ScavTrap " << name_ << MAGENTA
			  << " is now in Gate keeper mode!" << RESET << std::endl;
}