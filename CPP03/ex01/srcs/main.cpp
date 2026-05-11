// main.cpp
#include "ScavTrap.hpp"
#include <iostream>

int main(void)
{
    std::cout << "===== Construction / Destruction Chaining =====" << std::endl;
    {
        ScavTrap scav("Serena");
        std::cout << "HP: " << scav.getHitPoints()
            << " | EP: " << scav.getEnergyPoints()
            << " | AD: " << scav.getAttackDamage() << std::endl;
    }

    std::cout << "\n===== Default Constructor =====" << std::endl;
    {
        ScavTrap defaultScav;
        std::cout << "HP: " << defaultScav.getHitPoints()
            << " | EP: " << defaultScav.getEnergyPoints()
            << " | AD: " << defaultScav.getAttackDamage() << std::endl;
    }

    std::cout << "\n===== Copy Constructor =====" << std::endl;
    {
        ScavTrap original("Original");
        ScavTrap copy(original);
        std::cout << "Copy HP: " << copy.getHitPoints()
            << " | EP: " << copy.getEnergyPoints()
            << " | AD: " << copy.getAttackDamage() << std::endl;
    }

    std::cout << "\n===== Assignment Operator =====" << std::endl;
    {
        ScavTrap a("Alpha");
        ScavTrap b("Bravo");
        b = a;
    }

    std::cout << "\n===== ScavTrap Attack =====" << std::endl;
    {
        ScavTrap scav("Fighter");
        scav.attack("Enemy");
    }

    std::cout << "\n===== Guard Gate =====" << std::endl;
    {
        ScavTrap scav("Guardian");
        scav.guardGate();
    }

    std::cout << "\n===== Take Damage and Repair =====" << std::endl;
    {
        ScavTrap scav("Survivor");
        scav.takeDamage(30);
        scav.beRepaired(10);
    }

    std::cout << "\n===== Cannot Attack When Dead =====" << std::endl;
    {
        ScavTrap scav("Fallen");
        scav.takeDamage(100);
        scav.attack("Enemy");
        scav.beRepaired(5);
    }

    std::cout << "\n===== Cannot Attack Without Energy =====" << std::endl;
    {
        ScavTrap scav("Exhausted");
        for (unsigned int i = 0; i < 50; ++i)
            scav.attack("Dummy");
        scav.attack("Dummy");
        scav.beRepaired(5);
    }

    return (0);
}