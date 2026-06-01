#include "ClapTrap.hpp"
#include "Colors.hpp"
#include <iostream>

// ---------------------- Orthodox Canonical Form ------------------------------

ClapTrap::ClapTrap(void) :
	_name("Default"), _hitPoints(10),
	_energyPoints(10), _attackDamage(0)
{
	std::cout << GREEN UNDERLINE << "ClapTrap " << _name
		<< " default constructor called"
		<< RESET << std::endl;
}

ClapTrap::ClapTrap(const std::string &name) :
	_name(name), _hitPoints(10),
	_energyPoints(10), _attackDamage(0)
{
	std::cout << GREEN UNDERLINE << "ClapTrap " << _name
		<< " parameterized constructor called"
		<< RESET << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) :
	_name(other._name), _hitPoints(other._hitPoints),
	_energyPoints(other._energyPoints), _attackDamage(other._attackDamage)
{
	std::cout << GREEN UNDERLINE << "ClapTrap " << _name
		<< " copy constructor called"
		<< RESET << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
	std::cout << GREEN UNDERLINE << "ClapTrap " << _name
		<< " assigment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		_name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
		_attackDamage = other._attackDamage;
	}
	return (*this);
}

ClapTrap::~ClapTrap(void)
{
	std::cout << GREEN UNDERLINE << "ClapTrap " << _name
		<< " destructor called"
		<< RESET << std::endl;
}

// ---------------------- Public Methods ---------------------------------------

const std::string &ClapTrap::getName(void) const
{
	return (_name);
}

unsigned int ClapTrap::getHitPoints(void) const
{
	return (_hitPoints);
}

unsigned int ClapTrap::getEnergyPoints(void) const
{
	return (_energyPoints);
}

unsigned int ClapTrap::getAttackDamage(void) const
{
	return (_attackDamage);
}

void ClapTrap::setAttackDamage(unsigned int damage)
{
	_attackDamage = damage;
}

// ---------------------- Game Logic ------------------------------------------

void ClapTrap::attack(const std::string &target)
{
	if (_hitPoints == 0 || _energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name
			<< CYAN << " cannot attack!"
			<< RESET << std::endl;
		return ;
	}

	--_energyPoints;

	std::cout << "ClapTrap "
		<< _name << RED
		<< " attacks " << RESET
		<< target << ", causing "
		<< _attackDamage << " points of damage!"
		<< RESET << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name
			<< DIM << " is already destroyed!"
			<< RESET << std::endl;
		return ;
	}

	// Impedir Underflow
	// 10 - 15 = -5
	// unsigned int nao permite -5, logo vai para MAX_UINT
	if (amount >= _hitPoints)
		_hitPoints = 0;
	else
		_hitPoints = _hitPoints - amount;

	std::cout << "ClapTrap " << _name
		<< BLUE << " takes " << RESET << amount
		<< " points of damage! Hit points left: " << _hitPoints
		<< RESET << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints == 0 || _energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name
			<< YELLOW << " cannot be repaired!"
			<< RESET << std::endl;
		return ;
	}
	--_energyPoints;

	// Impedir Overflow
	// 4294967290 + 10 = 4294967300
	// Fica maior que o MAX_UINT, logo, voltaria a 0
	if (amount > MAX_HP - _hitPoints)
		_hitPoints = MAX_HP;
	else
		_hitPoints = _hitPoints + amount;

	std::cout << "ClapTrap " << _name
		<< GREEN << " repairs itself for " << RESET << amount
		<< " points! Hit points left: " << _hitPoints
		<< RESET << std::endl;
}
