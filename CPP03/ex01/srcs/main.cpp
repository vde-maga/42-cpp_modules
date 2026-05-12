#include "ClapTrap.hpp"
#include "Colors.hpp"
#include <iostream>

int main(void)
{
	bool all_passed = true;

	std::cout << "Starting ClapTrap unit tests" << std::endl << std::endl;

	// Test 1: Default Constructor
	{
		std::cout << MAGENTA << "Test: Default Constructor - verifying default name, hit points, energy points, attack damage..." << RESET << std::endl;
		ClapTrap ct;
		bool passed = true;
		if (ct.getName() != "Default" || ct.getHitPoints() != 10 ||
				ct.getEnergyPoints() != 10 || ct.getAttackDamage() != 0)
		{
			std::cerr << "  -> Test Failed: Default Constructor" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 2: Parameterized Constructor
	{
		std::cout << MAGENTA << "Test: Parameterized Constructor - creating ClapTrap(\"Bobby\") and verifying fields..." << RESET << std::endl;
		ClapTrap ct("Bobby");
		bool passed = true;
		if (ct.getName() != "Bobby" || ct.getHitPoints() != 10 ||
				ct.getEnergyPoints() != 10 || ct.getAttackDamage() != 0)
		{
			std::cerr << "  -> Test Failed: Parameterized Constructor" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 3: Copy Constructor
	{
		std::cout << MAGENTA << "Test: Copy Constructor - copy from an object with modified attack damage..." << RESET << std::endl;
		ClapTrap ct1("Copy");
		ct1.setAttackDamage(5);
		ClapTrap ct2(ct1);
		bool passed = true;
		if (ct2.getName() != "Copy" || ct2.getHitPoints() != 10 ||
				ct2.getEnergyPoints() != 10 || ct2.getAttackDamage() != 5)
		{
			std::cerr << "  -> Test Failed: Copy Constructor" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 4: Assignment Operator
	{
		std::cout << MAGENTA << "Test: Assignment Operator - assign one ClapTrap to another and verify name and attack damage..." << RESET << std::endl;
		ClapTrap ct1("Assign1");
		ct1.setAttackDamage(3);
		ClapTrap ct2("Assign2");
		ct2 = ct1;
		bool passed = true;
		if (ct2.getName() != "Assign1" || ct2.getAttackDamage() != 3)
		{
			std::cerr << "  -> Test Failed: Assignment Operator" << std::endl;
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 5: Attack and Repair behavior
	{
		std::cout << MAGENTA << "Test: Attack and Repair - attack consumes energy; repair increases hit points and consumes energy..." << RESET << std::endl;
		ClapTrap ct("Fighter");
		ct.setAttackDamage(2);
		bool passed = true;

		ct.attack("Enemy");
		if (ct.getEnergyPoints() != 9)
		{
			std::cerr << "  -> Test Failed: Attack energy drain" << std::endl;
			passed = false;
			all_passed = false;
		}

		ct.beRepaired(5);
		if (ct.getHitPoints() != 15 || ct.getEnergyPoints() != 8)
		{
			std::cerr << "  -> Test Failed: Repair" << std::endl;
			passed = false;
			all_passed = false;
		}

		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 6: Take Damage and overkill
	{
		std::cout << MAGENTA << "Test: Take Damage - reduce hit points and ensure they don't go below zero..." << RESET << std::endl;
		ClapTrap ct("Tank");
		bool passed = true;

		ct.takeDamage(4);
		if (ct.getHitPoints() != 6)
		{
			std::cerr << "  -> Test Failed: Take Damage" << std::endl;
			passed = false;
			all_passed = false;
		}

		ct.takeDamage(10);
		if (ct.getHitPoints() != 0)
		{
			std::cerr << "  -> Test Failed: Take Damage overkill" << std::endl;
			passed = false;
			all_passed = false;
		}

		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 7: Energy depletion after repeated attacks
	{
		std::cout << MAGENTA << "Test: Energy depletion - perform 10 attacks and verify energy reaches zero; further actions should be blocked..." << RESET << std::endl;
		ClapTrap ct("Exhausted");
		bool passed = true;

		for (unsigned int i = 0; i < 10; ++i)
		{
			ct.attack("Dummy");
		}
		if (ct.getEnergyPoints() != 0)
		{
			std::cerr << "  -> Test Failed: Energy depletion" << std::endl;
			passed = false;
			all_passed = false;
		}

		// Attempt one more action to ensure class handles zero energy gracefully
		ct.attack("Dummy");
		ct.beRepaired(1);

		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Test 8: Actions when hit points are zero
	{
		std::cout << MAGENTA << "Test: Hitpoints depletion - when HP is zero, actions should be blocked or handled safely..." << RESET << std::endl;
		ClapTrap ct("Dead");
		bool passed = true;

		ct.takeDamage(10);
		if (ct.getHitPoints() != 0)
		{
			std::cerr << "  -> Test Failed: Hitpoints depletion" << std::endl;
			passed = false;
			all_passed = false;
		}

		// Attempt actions while dead to ensure no negative behavior
		ct.attack("Dummy");
		ct.beRepaired(1);

		if (passed)
			std::cout << "  -> PASS" << std::endl;
		std::cout << '\n';
	}

	// Summary
	if (all_passed)
	{
		std::cout << "All tests passed!" << std::endl;
	}
	else
	{
		std::cout << "Some tests failed. See error messages above for details." << std::endl;
	}

	return (all_passed ? 0 : 1);
}

