#include "Zombie.hpp"
#include "Colors.hpp"
#include <iostream>
#include <string>
#include <new>

int main(void)
{
	bool all_passed = true;

	std::cout << "Starting Zombie unit tests"
		<< std::endl << std::endl;

	{
		std::cout << MAGENTA << "Test 1: randomChump - Stack allocation, should announce and auto-destruct..."
			<< RESET << std::endl;
		bool passed = true;
		try
		{
			randomChump("StackZ");
		}
		catch (...)
		{
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS"
				<< std::endl << std::endl;
		else
			std::cout << RED << "  -> FAIL"
				<< RESET << std::endl << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 2: newZombie - Heap allocation, manual deletion required..."
			<< RESET << std::endl;
		bool passed = false;
		try
		{
			Zombie *z = newZombie("HeapZ");
			if (z != NULL && z->getName() == "HeapZ")
				passed = true;
			else
				all_passed = false;

			z->announce();
			delete z;
		}
		catch (...)
		{
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS"
				<< std::endl << std::endl;
		else
			std::cout << RED << "  -> FAIL"
				<< RESET << std::endl << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 3: Empty Name - should handle gracefully without UB..."
			<< RESET << std::endl;
		bool passed = true;
		try
		{
			Zombie emptyZ("");
			if (emptyZ.getName() != "")
				passed = false;
			emptyZ.announce();

			randomChump("");

			Zombie *heapEmpty = newZombie("");
			heapEmpty->announce();
			delete heapEmpty;
		}
		catch (...)
		{
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS"
				<< std::endl << std::endl;
		else
			std::cout << RED << "  -> FAIL"
				<< RESET << std::endl << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 4: Copy Constructor - verifying deep copy of name..."
			<< RESET << std::endl;
		bool passed = false;
		Zombie original("OriginalZ");
		Zombie copy(original);
		if (copy.getName() == "OriginalZ")
			passed = true;
		else
			all_passed = false;

		if (passed)
			std::cout << "  -> PASS"
				<< std::endl << std::endl;
		else
			std::cout << RED << "  -> FAIL"
				<< RESET << std::endl << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 5: Assignment Operator - verifying assignment of name..."
			<< RESET << std::endl;
		bool passed = false;
		Zombie a("ZombieA");
		Zombie b("ZombieB");
		b = a;
		if (b.getName() == "ZombieA")
			passed = true;
		else
			all_passed = false;

		if (passed)
			std::cout << "  -> PASS"
				<< std::endl << std::endl;
		else
			std::cout << RED << "  -> FAIL"
				<< RESET << std::endl << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 6: Self-Assignment - should not crash or corrupt data..."
			<< RESET << std::endl;
		bool passed = false;
		Zombie self("SelfZ");

		// Silenciando o aviso do compilador propositalmente para testar a auto-atribuição
		// O compilador acha que isto é um typo, mas nós queremos testar se a classe sobrevive a isto.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
		self = self; // Teste defensivo extremo para operador=
#pragma clang diagnostic pop

		if (self.getName() == "SelfZ")
			passed = true;
		else
			all_passed = false;

		if (passed)
			std::cout << "  -> PASS"
				<< std::endl << std::endl;
		else
			std::cout << RED << "  -> FAIL"
				<< RESET << std::endl << std::endl;
	}

	{
		std::cout << MAGENTA << "Test 7: Massive Name - handling a very large string without crashing..." << RESET << std::endl;
		bool passed = true;
		try
		{
			std::string huge_name(10000, 'A');
			Zombie hugeZ(huge_name);
			if (hugeZ.getName() != huge_name)
			{
				passed = false;
			}
			hugeZ.announce();
		}
		catch (const std::bad_alloc &)
		{
			// É aceitável falhar por falta de memória, mas não pode crashar com UB
			std::cout << "  -> SKIPPED (bad_alloc, acceptable)"
				<< std::endl << std::endl;
			passed = true;
		}
		catch (...)
		{
			passed = false;
			all_passed = false;
		}
		if (passed)
			std::cout << "  -> PASS"
				<< std::endl << std::endl;
		else
			std::cout << RED << "  -> FAIL"
				<< RESET << std::endl << std::endl;
	}

	if (all_passed)
		std::cout << GREEN << "All Zombie tests passed!"
			<< RESET << std::endl;
	else
		std::cout << RED << "Some Zombie tests failed."
			<< RESET << std::endl;

	return (all_passed ? 0 : 1);
}
