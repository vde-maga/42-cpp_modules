#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Colors.hpp"
#include <iostream>

int main(void)
{
	bool all_passed = true;

	std::cout << "Starting HumanA & HumanB unit tests" << std::endl
			  << std::endl;

	{
		std::cout << MAGENTA << "Test 1: Subject Test - HumanA with reference..." << RESET << std::endl;
		bool passed = false;

		Weapon club("crude spiked club");
		HumanA bob("Bob", club);
		bob.attack();

		club.setType("some other type of club");
		bob.attack();

		if (club.getType() == "some other type of club")
			passed = true;
		else
			all_passed = false;

		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 2: Subject Test - HumanB with pointer..." << RESET << std::endl;
		bool passed = false;

		Weapon club("crude spiked club");
		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();

		club.setType("some other type of club");
		jim.attack();

		if (club.getType() == "some other type of club")
			passed = true;
		else
			all_passed = false;

		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 3: HumanB - Attacks without weapon (should not segfault/UB)..." << RESET << std::endl;
		bool passed = true;

		HumanB arthur("Arthur");
		arthur.attack();

		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 4: Empty strings - Nameless human and typeless weapon..." << RESET << std::endl;
		bool passed = true;

		Weapon voidWeapon("");
		HumanA nameless("", voidWeapon);
		nameless.attack();

		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 5: HumanB - Re-arming with a different weapon..." << RESET << std::endl;
		bool passed = false;

		Weapon sword("Longsword");
		Weapon dagger("Rusty Dagger");

		HumanB rogue("Rogue");
		rogue.setWeapon(sword);
		rogue.attack();

		rogue.setWeapon(dagger);
		rogue.attack();

		if (dagger.getType() == "Rusty Dagger")
			passed = true;
		else
			all_passed = false;

		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
	}

	if (all_passed)
		std::cout << GREEN << "All HumanA & HumanB tests passed!" << std::endl
				  << RESET;
	else
		std::cout << RED << "Some HumanA & HumanB tests failed." << std::endl
				  << RESET;

	return (all_passed ? 0 : 1);
}
