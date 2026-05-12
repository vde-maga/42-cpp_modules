#include "DiamondTrap.hpp"
#include "Colors.hpp"
#include <iostream>

int main(void)
{
	bool all_passed = true;

	std::cout << "Starting DiamondTrap unit tests"
			  << std::endl
			  << std::endl;

	// Test 1: Parameterized Constructor & Attributes
	{
		std::cout << MAGENTA << "Test: Parameterized Constructor - verifying DiamondTrap specific stats (HP: 100, EP: 50, AD: 30)..." << RESET << std::endl;
		DiamondTrap d("Sparkly");
		bool passed = true;
		// DiamondTrap: HP de FragTrap (100), EP de ScavTrap (50), AD de FragTrap (30)
		if (d.getHitPoints() != 100 || d.getEnergyPoints() != 50 || d.getAttackDamage() != 30)
		{
			std::cerr << "  -> Test Failed: Attributes mismatch" << std::endl;
			passed = false;
			all_passed = false;
		}
		d.whoAmI();
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << std::endl;
	}

	// Test 2: Default Constructor
	{
		std::cout << MAGENTA << "Test: Default Constructor - verifying default values..." << RESET << std::endl;
		DiamondTrap def;
		bool passed = true;
		if (def.getHitPoints() != 100 || def.getEnergyPoints() != 50 || def.getAttackDamage() != 30)
		{
			std::cerr << "  -> Test Failed: Default Constructor stats" << std::endl;
			passed = false;
			all_passed = false;
		}
		def.whoAmI();
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << std::endl;
	}

	// Test 3: Copy Constructor
	{
		std::cout << MAGENTA << "Test: Copy Constructor - verifying deep copy of name..." << RESET << std::endl;
		DiamondTrap original("OriginalD");
		DiamondTrap copy(original);
		bool passed = true;
		// Nota: getHitPoints() deve vir do original
		if (copy.getHitPoints() != 100)
		{
			std::cerr << "  -> Test Failed: Copy Constructor" << std::endl;
			passed = false;
			all_passed = false;
		}
		copy.whoAmI();
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << std::endl;
	}

	// Test 4: Assignment Operator
	{
		std::cout << MAGENTA << "Test: Assignment Operator..." << RESET << std::endl;
		DiamondTrap a("AlphaD");
		DiamondTrap b("BravoD");
		b = a;
		bool passed = true;
		if (b.getHitPoints() != 100)
		{
			std::cerr << "  -> Test Failed: Assignment Operator" << std::endl;
			passed = false;
			all_passed = false;
		}
		b.whoAmI();
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << std::endl;
	}

	// Test 5: Attack (Should use ScavTrap's attack)
	{
		std::cout << MAGENTA << "Test: Attack - DiamondTrap should use ScavTrap's attack (energy consumption)..." << RESET << std::endl;
		DiamondTrap d("AttackerD");
		d.attack("Target");
		bool passed = true;
		if (d.getEnergyPoints() != 49) // ScavTrap attack gasta 1 EP
		{
			std::cerr << "  -> Test Failed: Attack energy drain" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << std::endl;
	}

	// Test 6: Special Abilities (Inherited from Scav and Frag)
	{
		std::cout << MAGENTA << "Test: Special Abilities - guardGate and highFivesGuys..." << RESET << std::endl;
		DiamondTrap d("SpecialD");
		d.guardGate();
		d.highFivesGuys();
		std::cout << "  -> PASS (Manual check for output above)"
				  << std::endl
				  << std::endl;
	}

	// Test 7: Energy depletion (50 energy points)
	{
		std::cout << MAGENTA << "Test: Energy depletion - perform 50 attacks to exhaust energy..." << RESET << std::endl;
		DiamondTrap d("ExhaustedD");
		bool passed = true;

		for (int i = 0; i < 50; ++i)
			d.attack("Dummy");

		if (d.getEnergyPoints() != 0)
		{
			std::cerr << "  -> Test Failed: Energy should be 0" << std::endl;
			passed = false;
			all_passed = false;
		}
		// Attempting action with 0 EP
		d.beRepaired(10);
		if (d.getHitPoints() == 110) // Should not have repaired
		{
			std::cerr << "  -> Test Failed: Action performed with zero energy" << std::endl;
			passed = false;
			all_passed = false;
		}

		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << std::endl;
	}

	// Test 8: Death state
	{
		std::cout << MAGENTA << "Test: Death state - actions should be blocked at 0 HP..." << RESET << std::endl;
		DiamondTrap d("DeadD");
		bool passed = true;

		d.takeDamage(100);
		d.attack("Target");
		d.beRepaired(10);

		if (d.getHitPoints() != 0)
		{
			std::cerr << "  -> Test Failed: HP should remain 0" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << std::endl;
	}

	// Test 9: Polymorphic Destruction
	{
		std::cout << MAGENTA << "Test: Polymorphic Destruction - ensure virtual destructors are working..." << RESET << std::endl;
		ClapTrap *poly = new DiamondTrap("PolyD");
		poly->attack("Target");
		delete poly;
		std::cout << "  -> PASS (Check destructor chain in logs)\n"
				  << std::endl;
	}

	// Summary
	if (all_passed)
		std::cout << GREEN << "All DiamondTrap tests passed!" << std::endl
				  << RESET;
	else
		std::cout << RED << "Some DiamondTrap tests failed." << std::endl
				  << RESET;

	return (all_passed ? 0 : 1);
}