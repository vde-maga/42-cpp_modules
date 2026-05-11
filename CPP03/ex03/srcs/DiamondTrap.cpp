#include "DiamondTrap.hpp"
#include "Colors.hpp"
#include <iostream>

// ---------------------- Orthodox Canonical Form ------------------------------

DiamondTrap::DiamondTrap(void) : ClapTrap("Default_clap_name"), ScavTrap(),
    FragTrap(), name_("Default")
{
    hitPoints_ = 100;
    energyPoints_ = 50;
    attackDamage_ = 30;
    std::cout << GREEN UNDERLINE << "DiamondTrap " << name_
        << " default constructor called" << RESET << std::endl;
}

DiamondTrap::DiamondTrap(const std::string &name) : ClapTrap(name + "_clap_name"),
    ScavTrap(name), FragTrap(name), name_(name)
{
    hitPoints_ = 100;
    energyPoints_ = 50;
    attackDamage_ = 30;
    std::cout << GREEN UNDERLINE << "DiamondTrap " << name_
        << " parameterized constructor called" << RESET << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other) : ClapTrap(other),
    ScavTrap(other), FragTrap(other), name_(other.name_)
{
    std::cout << GREEN UNDERLINE << "DiamondTrap " << name_
        << " copy constructor called" << RESET << std::endl;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &other)
{
    std::cout << GREEN UNDERLINE << "DiamondTrap " << name_
        << " assigment operator called" << RESET << std::endl;
    if (this != &other)
    {
        ClapTrap::operator=(other);
        name_ = other.name_;
    }
    return (*this);
}

DiamondTrap::~DiamondTrap(void)
{
    std::cout << GREEN UNDERLINE << "DiamondTrap " << name_
        << " destructor called" << RESET << std::endl;
}

// ---------------------- Public Methods ---------------------------------------

void DiamondTrap::attack(const std::string &target)
{
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI(void) const
{
    std::cout << "DiamondTrap name: " << name_
        << ", ClapTrap name: " << ClapTrap::name_ << std::endl;
}