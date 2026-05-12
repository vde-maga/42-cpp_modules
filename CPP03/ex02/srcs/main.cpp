#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "Colors.hpp"
#include <iostream>

int main(void)
{
	bool all_passed = true;

	std::cout << "Starting FragTrap unit tests\n" << std::endl;

	// Test 1: Default Constructor
	{
		std::cout << MAGENTA << "Test: Default Constructor - HP 100, EP 100, AD 30" << RESET << std::endl;
		FragTrap frag;
		bool passed = true;
		if (frag.getHitPoints() != 100 || frag.getEnergyPoints() != 100
				|| frag.getAttackDamage() != 30)
		{
			std::cerr << "  -> Test Failed: Default Constructor attributes" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 2: Parameterized Constructor
	{
		std::cout << MAGENTA << "Test: Parameterized Constructor - FragTrap(\"Fraggy\")" << RESET << std::endl;
		FragTrap frag("Fraggy");
		bool passed = true;
		if (frag.getName() != "Fraggy" || frag.getHitPoints() != 100)
		{
			std::cerr << "  -> Test Failed: Parameterized Constructor name/HP" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 3: Copy Constructor
	{
		std::cout << MAGENTA << "Test: Copy Constructor - Deep copy verification" << RESET << std::endl;
		FragTrap original("Original");
		original.takeDamage(10);
		FragTrap copy(original);
		bool passed = true;
		if (copy.getName() != "Original" || copy.getHitPoints() != 90)
		{
			std::cerr << "  -> Test Failed: Copy Constructor state" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 4: Assignment Operator
	{
		std::cout << MAGENTA << "Test: Assignment Operator" << RESET << std::endl;
		FragTrap a("FragA");
		FragTrap b("FragB");
		b = a;
		bool passed = true;
		if (b.getName() != "FragA")
		{
			std::cerr << "  -> Test Failed: Assignment Operator" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 5: Attack and Energy Consumption
	{
		std::cout << MAGENTA << "Test: FragTrap Attack - verify energy drain" << RESET << std::endl;
		FragTrap frag("Attacker");
		bool passed = true;
		frag.attack("Target");
		if (frag.getEnergyPoints() != 99)
		{
			std::cerr << "  -> Test Failed: Attack should consume 1 EP" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 6: High Fives Guys
	{
		std::cout << MAGENTA << "Test: Special Capacity - highFivesGuys()" << RESET << std::endl;
		FragTrap frag("Happy");
		frag.highFivesGuys();
		std::cout << "  -> PASS (Visual verification required for message)\n" << std::endl;
	}

	// Test 7: Death and Action Blocking
	{
		std::cout << MAGENTA << "Test: Death State - No actions should be possible at 0 HP" << RESET << std::endl;
		FragTrap frag("Survivor");
		frag.takeDamage(100);
		bool passed = true;

		unsigned int ep_before = frag.getEnergyPoints();
		frag.attack("Dummy");
		frag.beRepaired(10);

		if (frag.getHitPoints() != 0 || frag.getEnergyPoints() != ep_before)
		{
			std::cerr << "  -> Test Failed: Actions performed while dead" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 8: Energy Depletion
	{
		std::cout << MAGENTA << "Test: Energy Depletion - 100 attacks to reach zero" << RESET << std::endl;
		FragTrap frag("Exhausted");
		bool passed = true;
		for (int i = 0; i < 100; ++i)
			frag.attack("Practice Target");

		if (frag.getEnergyPoints() != 0)
		{
			std::cerr << "  -> Test Failed: Energy should be 0" << std::endl;
			passed = false;
			all_passed = false;
		}

		frag.attack("One more"); // Should not work
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 9: Polymorphic Destruction
	{
		std::cout << MAGENTA << "Test: Polymorphic Destruction (ClapTrap* = new FragTrap)" << RESET << std::endl;
		ClapTrap *poly = new FragTrap("PolyFrag");
		delete poly; // Ensure virtual destructor is working
		std::cout << "  -> PASS (Check logs for FragTrap -> ClapTrap destructor order)\n" << std::endl;
	}

	// Summary
	if (all_passed)
		std::cout << GREEN << "All FragTrap tests passed!" << RESET << std::endl;
	else
		std::cout << RED << "Some FragTrap tests failed." << RESET << std::endl;

	return (all_passed ? 0 : 1);
}
