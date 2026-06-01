#include "FragTrap.hpp" // Inclui indiretamente ClapTrap e ScavTrap
#include "ScavTrap.hpp"
#include "Colors.hpp"
#include <iostream>
#include <string>

// --------------------- Test Framework Macros & Helpers ---------------------

static int g_tests_passed = 0;
static int g_tests_total = 0;

static void assertTest(bool condition, const std::string &test_name)
{
	++g_tests_total;
	if (condition)
	{
		++g_tests_passed;
		std::cout << BRIGHT_GREEN << "[PASS] " << RESET << test_name << std::endl;
	}
	else
	{
		std::cout << BRIGHT_RED << "[FAIL] " << RESET << test_name << std::endl;
	}
}

static void printSection(const std::string &title)
{
	std::cout << std::endl
			  << BOLD BG_MAGENTA << " " << title << " "
			  << RESET << std::endl;
}

// ----------------------------- Destructive Tests ----------------------------

void testFragConstructionDestruction()
{
	printSection("1. Frag Construction & Destruction Chaining");
	std::cout << BRIGHT_YELLOW << "--- Creating FragTrap 'Chainer' ---" << RESET << std::endl;
	{
		FragTrap chainer("Chainer");
	} // Destrutor chamado aqui
	std::cout << BRIGHT_YELLOW << "--- FragTrap 'Chainer' destroyed ---" << RESET << std::endl;
	assertTest(true, "Visual check: ClapTrap built first, destroyed last");
}

void testFragInitialStats()
{
	printSection("2. FragTrap Initial Stats (Subject Rules)");

	FragTrap ft("Stats");

	assertTest(ft.getHitPoints() == 100, "FragTrap Initial HP must be 100");
	assertTest(ft.getEnergyPoints() == 100, "FragTrap Initial EP must be 100");
	assertTest(ft.getAttackDamage() == 30, "FragTrap Initial AD must be 30");
}

void testFragNormalActions()
{
	printSection("3. FragTrap Normal Actions & Energy Drain");

	FragTrap ft("Normal");

	ft.attack("Target1");
	assertTest(ft.getEnergyPoints() == 99, "FragTrap attack costs 1 EP");

	ft.beRepaired(20);
	assertTest(ft.getEnergyPoints() == 98, "FragTrap repair costs 1 EP");
	assertTest(ft.getHitPoints() == 120, "FragTrap repair adds HP correctly");
}

void testFragDeathAndRestrictions()
{
	printSection("4. FragTrap Death & Action Restrictions");

	FragTrap ft("Dead");
	ft.takeDamage(100);

	assertTest(ft.getHitPoints() == 0, "FragTrap taking full damage kills it");

	ft.attack("Ghost");
	assertTest(ft.getEnergyPoints() == 100, "Dead FragTrap cannot spend EP to attack"); // CORRIGIDO: 100 em vez de 99

	ft.beRepaired(10);
	assertTest(ft.getHitPoints() == 0, "Dead FragTrap cannot be repaired");
}

void testFragOverkill()
{
	printSection("5. FragTrap Overkill (No Underflow)");

	FragTrap ft("Overkill");
	ft.takeDamage(9999);

	assertTest(ft.getHitPoints() == 0, "FragTrap HP cannot go below 0 on massive damage");
}

void testFragEnergyDepletion()
{
	printSection("6. FragTrap Energy Depletion (100 Actions Max)");

	FragTrap ft("Tired");

	for (int i = 0; i < 100; ++i) // Pré-incremento
		ft.attack("Dummy");

	assertTest(ft.getEnergyPoints() == 0, "FragTrap EP reaches 0 after 100 attacks");

	ft.attack("Exhausted");
	ft.beRepaired(1);

	assertTest(ft.getHitPoints() == 100, "No EP means no actions at all");
}

void testFragOverflowRepair()
{
	printSection("7. FragTrap Destructive Overflow Test (MAX UINT)");

	FragTrap ft("Overflow");
	const unsigned int max_uint = static_cast<unsigned int>(-1);

	ft.beRepaired(max_uint);
	assertTest(ft.getHitPoints() == max_uint, "FragTrap Repair to MAX_UINT succeeds safely");

	ft.beRepaired(1);
	assertTest(ft.getHitPoints() == max_uint, "FragTrap HP caps at MAX_UINT instead of overflowing");
}

void testHighFives()
{
	printSection("8. Special Ability: High Fives");

	FragTrap ft("Bro");
	ft.highFivesGuys();
	assertTest(true, "High fives executed without crash");
}

void testAllTrapsCoexistence()
{
	printSection("9. Cross-Trap Integrity (Polymorphism prep)");

	ClapTrap c("Base");
	ScavTrap s("Mid");
	FragTrap f("Top");

	c.attack("Target");
	s.attack("Target");
	f.attack("Target");

	assertTest(c.getEnergyPoints() == 9, "ClapTrap still uses its own EP rules");
	assertTest(s.getEnergyPoints() == 49, "ScavTrap still uses its own EP rules");
	assertTest(f.getEnergyPoints() == 99, "FragTrap still uses its own EP rules");
}

int main()
{
	std::cout << BOLD YELLOW << "STARTING FRAGTRAP DESTRUCTIVE TEST SUITE" << RESET << std::endl;

	testFragConstructionDestruction();
	testFragInitialStats();
	testFragNormalActions();
	testFragDeathAndRestrictions();
	testFragOverkill();
	testFragEnergyDepletion();
	testFragOverflowRepair();
	testHighFives();
	testAllTrapsCoexistence();

	std::cout << std::endl
			  << BOLD << "=====================================" << RESET << std::endl;
	std::cout << BOLD << "TOTAL: " << g_tests_passed << "/" << g_tests_total << " tests passed." << RESET << std::endl;

	if (g_tests_passed == g_tests_total)
		std::cout << BRIGHT_GREEN << "ALL TESTS PASSED!" << RESET << std::endl;
	else
		std::cout << BRIGHT_RED << "SOME TESTS FAILED!" << RESET << std::endl;

	return (g_tests_passed != g_tests_total);
}