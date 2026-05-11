#include "FragTrap.hpp"
#include "Colors.hpp"
#include <iostream>

// ---------------------- Orthodox Canonical Form ------------------------------

FragTrap::FragTrap(void) : ClapTrap()
{
    hitPoints_ = 100;
    energyPoints_ = 100;
    attackDamage_ = 30;
    std::cout << GREEN UNDERLINE << "FragTrap " << name_
        << " default constructor called" << RESET << std::endl;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name)
{
    hitPoints_ = 100;
    energyPoints_ = 100;
    attackDamage_ = 30;
    std::cout << GREEN UNDERLINE << "FragTrap " << name_
        << " parameterized constructor called" << RESET << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other)
{
    std::cout << GREEN UNDERLINE << "FragTrap " << name_
        << " copy constructor called" << RESET << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
    std::cout << GREEN UNDERLINE << "FragTrap " << name_
        << " assigment operator called" << RESET << std::endl;
    if (this != &other)
        ClapTrap::operator=(other);
    return (*this);
}

FragTrap::~FragTrap(void)
{
    std::cout << GREEN UNDERLINE << "FragTrap " << name_
        << " destructor called" << RESET << std::endl;
}

// ---------------------- Public Methods ---------------------------------------

void FragTrap::attack(const std::string &target)
{
    if (hitPoints_ == 0 || energyPoints_ == 0)
    {
        std::cout << "FragTrap " << name_ << CYAN << " cannot attack!"
            << RESET << std::endl;
        return ;
    }
    energyPoints_--;
    std::cout << "FragTrap " << name_ << RED << " attacks " << RESET << target
        << ", causing " << attackDamage_ << " points of damage!" << std::endl;
}

void FragTrap::highFivesGuys(void) const
{
    std::cout << "FragTrap " << name_ << MAGENTA
        << " requests a positive high-fives!" << RESET << std::endl;
}