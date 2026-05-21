#include "Colors.hpp"
#include "Zombie.hpp"
#include <iostream>
#include <new>

int main(void)
{
	bool all_passed = true;

	std::cout << "Starting ZombieHorde unit tests"
		<< std::endl << std::endl;

	{
		std::cout << MAGENTA << "Test 1: Normal Horde - Allocate 5 zombies, announce, and delete..."
			<< RESET << std::endl;
		bool passed = false;
		Zombie *horde = zombieHorde(5, "HordeZ");
		if (horde != NULL)
		{
			passed = true;
			for (int i = 0; i < 5; ++i)
			{
				if (horde[i].getName() != "HordeZ")
					passed = false;
				horde[i].announce();
			}
			delete[] horde;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
		{
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
			all_passed = false;
		}
	}

	{
		std::cout << MAGENTA << "Test 2: Single Zombie Horde - N=1, ensure correct alloc/delete..."
			<< RESET << std::endl;
		bool passed = false;
		Zombie *horde = zombieHorde(1, "SoloZ");
		if (horde != NULL && horde->getName() == "SoloZ")
		{
			passed = true;
			horde->announce();
			delete[] horde;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
		{
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
			all_passed = false;
		}
	}

	{
		std::cout << MAGENTA << "Test 3: Zero Zombies - N=0, should return NULL and not crash..."
			<< RESET << std::endl;
		bool passed = false;
		Zombie *horde = zombieHorde(0, "ZeroZ");
		if (horde == NULL)
			passed = true;
		delete[] horde;

		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
		{
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
			all_passed = false;
		}
	}

	{
		std::cout << MAGENTA << "Test 4: Negative N - Should defend against bad_alloc or UB..." << RESET << std::endl;
		bool passed = false;
		Zombie *horde = zombieHorde(-5, "NegZ");
		if (horde == NULL)
			passed = true;
		delete[] horde;

		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
		{
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
			all_passed = false;
		}
	}

	{
		std::cout << MAGENTA << "Test 5: Empty Name - Should handle gracefully without crashing..." << RESET << std::endl;
		bool passed = false;
		Zombie *horde = zombieHorde(3, "");
		if (horde != NULL && horde->getName() == "")
		{
			passed = true;
			for (int i = 0; i < 3; ++i)
				horde[i].announce();
			delete[] horde;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
		{
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
			all_passed = false;
		}
	}

	{
		std::cout << MAGENTA << "Test 6: Massive Allocation - 100 zombies (stress test)..." << RESET << std::endl;
		bool passed = true;
		try
		{
			Zombie *horde = zombieHorde(100, "MassiveZ");
			if (horde != NULL)
				delete[] horde;
			else
				passed = false;
		}
		catch (const std::bad_alloc &)
		{
			std::cout << "  -> SKIPPED (bad_alloc, acceptable)" << std::endl
					  << std::endl;
			passed = true;
		}
		catch (...)
		{
			passed = false;
		}
		if (passed)
			std::cout << "  -> PASS" << std::endl
					  << std::endl;
		else
		{
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
			all_passed = false;
		}
	}

	if (all_passed)
		std::cout << GREEN << "All ZombieHorde tests passed!" << std::endl
				  << RESET;
	else
		std::cout << RED << "Some ZombieHorde tests failed." << std::endl
				  << RESET;

	return (all_passed ? 0 : 1);
}
