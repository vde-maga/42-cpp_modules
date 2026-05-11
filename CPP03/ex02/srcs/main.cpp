#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int main(void)
{
    std::cout << "===== FragTrap Construction / Destruction Chaining =====" << std::endl;
    {
        FragTrap frag("Fraggy");
        std::cout << "HP: " << frag.getHitPoints()
            << " | EP: " << frag.getEnergyPoints()
            << " | AD: " << frag.getAttackDamage() << std::endl;
    }

    std::cout << "\n===== FragTrap Default Constructor =====" << std::endl;
    {
        FragTrap defaultFrag;
        std::cout << "HP: " << defaultFrag.getHitPoints()
            << " | EP: " << defaultFrag.getEnergyPoints()
            << " | AD: " << defaultFrag.getAttackDamage() << std::endl;
    }

    std::cout << "\n===== FragTrap Copy Constructor =====" << std::endl;
    {
        FragTrap original("OriginalFrag");
        FragTrap copy(original);
        std::cout << "Copy HP: " << copy.getHitPoints()
            << " | EP: " << copy.getEnergyPoints()
            << " | AD: " << copy.getAttackDamage() << std::endl;
    }

    std::cout << "\n===== FragTrap Assignment Operator =====" << std::endl;
    {
        FragTrap a("FragA");
        FragTrap b("FragB");
        b = a;
    }

    std::cout << "\n===== FragTrap Attack =====" << std::endl;
    {
        FragTrap frag("AttackerFrag");
        frag.attack("EnemyTarget");
    }

    std::cout << "\n===== FragTrap High Fives =====" << std::endl;
    {
        FragTrap frag("HappyFrag");
        frag.highFivesGuys();
    }

    std::cout << "\n===== FragTrap Take Damage and Repair =====" << std::endl;
    {
        FragTrap frag("SurvivorFrag");
        frag.takeDamage(40);
        frag.beRepaired(20);
    }

    std::cout << "\n===== FragTrap Cannot Attack When Dead =====" << std::endl;
    {
        FragTrap frag("DeadFrag");
        frag.takeDamage(100);
        frag.attack("EnemyTarget");
        frag.beRepaired(10);
    }

    std::cout << "\n===== FragTrap Cannot Attack Without Energy =====" << std::endl;
    {
        FragTrap frag("ExhaustedFrag");
        for (unsigned int i = 0; i < 100; ++i)
            frag.attack("DummyTarget");
        frag.attack("DummyTarget");
        frag.beRepaired(10);
    }

    std::cout << "\n===== Polymorphic Destruction Test =====" << std::endl;
    {
        ClapTrap* poly = new FragTrap("PolyFrag");
        poly->attack("Target");
        delete poly;
    }

    return (0);
}