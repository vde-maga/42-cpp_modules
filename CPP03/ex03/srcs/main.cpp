#include "DiamondTrap.hpp"
#include <iostream>

int main(void)
{
    std::cout << "===== DiamondTrap Construction / Destruction Chaining =====" << std::endl;
    {
        DiamondTrap d("Diamond");
        std::cout << "HP: " << d.getHitPoints()
            << " | EP: " << d.getEnergyPoints()
            << " | AD: " << d.getAttackDamage() << std::endl;
        d.whoAmI();
    }

    std::cout << "\n===== DiamondTrap Default Constructor =====" << std::endl;
    {
        DiamondTrap def;
        std::cout << "HP: " << def.getHitPoints()
            << " | EP: " << def.getEnergyPoints()
            << " | AD: " << def.getAttackDamage() << std::endl;
        def.whoAmI();
    }

    std::cout << "\n===== DiamondTrap Copy Constructor =====" << std::endl;
    {
        DiamondTrap original("OriginalD");
        DiamondTrap copy(original);
        copy.whoAmI();
    }

    std::cout << "\n===== DiamondTrap Assignment Operator =====" << std::endl;
    {
        DiamondTrap a("AlphaD");
        DiamondTrap b("BravoD");
        b = a;
        b.whoAmI();
    }

    std::cout << "\n===== DiamondTrap Attack (ScavTrap) =====" << std::endl;
    {
        DiamondTrap d("AttackerD");
        d.attack("Target");
    }

    std::cout << "\n===== DiamondTrap Special Abilities =====" << std::endl;
    {
        DiamondTrap d("SpecialD");
        d.guardGate();
        d.highFivesGuys();
    }

    std::cout << "\n===== DiamondTrap Take Damage and Repair =====" << std::endl;
    {
        DiamondTrap d("SurvivorD");
        d.takeDamage(40);
        d.beRepaired(20);
    }

    std::cout << "\n===== DiamondTrap Cannot Attack When Dead =====" << std::endl;
    {
        DiamondTrap d("DeadD");
        d.takeDamage(100);
        d.attack("Target");
        d.beRepaired(10);
    }

    std::cout << "\n===== DiamondTrap Cannot Attack Without Energy =====" << std::endl;
    {
        DiamondTrap d("ExhaustedD");
        for (unsigned int i = 0; i < 50; ++i)
            d.attack("Dummy");
        d.attack("Dummy");
        d.beRepaired(5);
    }

    std::cout << "\n===== Polymorphic Destruction Test =====" << std::endl;
    {
        ClapTrap* poly = new DiamondTrap("PolyD");
        poly->attack("Target");
        delete poly;
    }

    return (0);
}