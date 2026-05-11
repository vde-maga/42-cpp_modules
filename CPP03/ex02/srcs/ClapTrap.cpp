#include "ClapTrap.hpp"
#include "Colors.hpp"
#include <iostream>

// ---------------------- Orthodox Canonical Form ------------------------------

ClapTrap::ClapTrap(void) : name_("Default"), hitPoints_(10), energyPoints_(10),
    attackDamage_(0)
{
    std::cout << GREEN UNDERLINE << "ClapTrap " << name_ << " default constructor called" << RESET << std::endl;
}

ClapTrap::ClapTrap(const std::string &name) : name_(name), hitPoints_(10),
    energyPoints_(10), attackDamage_(0)
{
    std::cout << GREEN UNDERLINE << "ClapTrap " << name_ << " parameterized constructor called" << RESET << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) : name_(other.name_),
    hitPoints_(other.hitPoints_), energyPoints_(other.energyPoints_),
    attackDamage_(other.attackDamage_)
{
    std::cout << GREEN UNDERLINE << "ClapTrap " << name_ << " copy constructor called" << RESET << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
    std::cout << GREEN UNDERLINE << "ClapTrap " << name_ << " assigment operator called" << RESET << std::endl;
    if (this != &other)
    {
        name_ = other.name_;
        hitPoints_ = other.hitPoints_;
        energyPoints_ = other.energyPoints_;
        attackDamage_ = other.attackDamage_;
    }
    return (*this);
}

ClapTrap::~ClapTrap(void)
{
    std::cout << GREEN UNDERLINE << "ClapTrap " << name_ << " destructor called" << RESET << std::endl;
}

// ---------------------- Public Methods ---------------------------------------
// Getters
const std::string &ClapTrap::getName(void) const
{
    return (name_);
}

unsigned int ClapTrap::getHitPoints(void) const
{
    return (hitPoints_);
}

unsigned int ClapTrap::getEnergyPoints(void) const
{
    return (energyPoints_);
}

unsigned int ClapTrap::getAttackDamage(void) const
{
    return (attackDamage_);
}

// Setters

void ClapTrap::setAttackDamage(unsigned int damage)
{
    attackDamage_ = damage;
}

// Other Functions

void ClapTrap::attack(const std::string &target)
{
    if (hitPoints_ == 0 || energyPoints_ == 0)
    {
        std::cout << "ClapTrap " << name_ << CYAN <<" cannot attack!"
            << RESET << std::endl;
        return ;
    }
    energyPoints_--;
    std::cout << "ClapTrap " << name_ << RED <<" attacks " << RESET << target
        << ", causing " << attackDamage_ << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (amount >= hitPoints_)
        hitPoints_ = 0;
    else
        hitPoints_ = hitPoints_ - amount;
    std::cout << "ClapTrap " << name_ << BLUE <<" takes " << RESET << amount
        << " points of damage! Hit points left: " << hitPoints_ << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (hitPoints_ == 0 || energyPoints_ == 0)
    {
        std::cout << "ClapTrap " << name_ << YELLOW <<" cannot be repaired!"
            << RESET << std::endl;
        return ;
    }
    energyPoints_--;
    if (hitPoints_ > hitPoints_ + amount)
        hitPoints_ = static_cast<unsigned int>(-1);
    else
        hitPoints_ = hitPoints_ + amount;
    std::cout << "ClapTrap " << name_ << GREEN << " repairs itself for "
        << RESET << amount << " points! Hit points left: " << hitPoints_ << std::endl;
}