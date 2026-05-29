#include "ClapTrap.hpp"
#include "Colors.hpp"
#include <iostream>
#include <string>

// --------------------- Test Framework Macros & Helpers ---------------------

static int	g_tests_passed = 0;
static int	g_tests_total = 0;

static void	assertTest(bool condition, const std::string &test_name)
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

static void	printSection(const std::string &title)
{
	std::cout << std::endl << BOLD BG_BLUE << " " << title << " " << RESET << std::endl;
}

// ----------------------------- Destructive Tests ----------------------------

void	testOrthodoxCanonicalForm(void)
{
	ClapTrap	c;

	printSection("1. Orthodox Canonical Form");
	ClapTrap a("Alpha");
	ClapTrap b(a);
	c = a;
	assertTest(a.getName() == "Alpha", "Parameterized constructor sets name");
	assertTest(b.getName() == "Alpha", "Copy constructor copies name");
	assertTest(c.getName() == "Alpha", "Assignment operator copies name");
}

void	testInitialStats(void)
{
	printSection("2. Initial Stats (Subject Rules)");
	ClapTrap ct("Stats");
	assertTest(ct.getHitPoints() == 10, "Initial HP must be 10");
	assertTest(ct.getEnergyPoints() == 10, "Initial EP must be 10");
	assertTest(ct.getAttackDamage() == 0, "Initial AD must be 0");
}

void	testNormalActions(void)
{
	printSection("3. Normal Actions & Energy Drain");
	ClapTrap ct("Normal");
	ct.attack("Target1");
	assertTest(ct.getEnergyPoints() == 9, "Attack costs 1 EP");
	ct.beRepaired(5);
	assertTest(ct.getEnergyPoints() == 8, "Repair costs 1 EP");
	assertTest(ct.getHitPoints() == 15, "Repair adds HP correctly");
}

void	testDeathAndRestrictions(void)
{
	printSection("4. Death & Action Restrictions");
	ClapTrap ct("Dead");
	ct.takeDamage(10);
	assertTest(ct.getHitPoints() == 0, "Taking full damage kills ClapTrap");
	ct.attack("Ghost"); // Não deve ter efeito
	assertTest(ct.getEnergyPoints() == 10,
		"Dead ClapTrap cannot spend EP to attack");
	ct.beRepaired(10); // Não deve ter efeito
	assertTest(ct.getHitPoints() == 0, "Dead ClapTrap cannot be repaired");
}

void	testOverkillDamage(void)
{
	printSection("5. Overkill (No Underflow)");
	ClapTrap ct("Overkill");
	ct.takeDamage(9999);
	assertTest(ct.getHitPoints() == 0,
		"HP cannot go below 0 on massive damage");
}

void	testEnergyDepletion(void)
{
	printSection("6. Energy Depletion (10 Actions Max)");
	ClapTrap ct("Tired");
	for (int i = 0; i < 10; ++i) // Pré-incremento
		ct.attack("Dummy");
	assertTest(ct.getEnergyPoints() == 0, "EP reaches 0 after 10 attacks");
	ct.attack("Exhausted"); // Sem energia
	ct.beRepaired(1);       // Sem energia
	assertTest(ct.getHitPoints() == 10, "No EP means no actions at all");
}

void	testDestructiveOverflowRepair(void)
{
	const unsigned int	max_uint = static_cast<unsigned int>(-1);

	printSection("7. Destructive Overflow Test (MAX UINT)");
	ClapTrap ct("Overflow");
	ct.beRepaired(max_uint);
	assertTest(ct.getHitPoints() == max_uint,
		"Repair to MAX_UINT succeeds safely");
	ct.beRepaired(1); // Iria dar overflow se não houvesse proteção!
	assertTest(ct.getHitPoints() == max_uint,
		"HP caps at MAX_UINT instead of overflowing");
}

void	testZeroDamageAndRepair(void)
{
	printSection("8. Edge Cases: Zero Values");
	ClapTrap ct("Zero");
	ct.takeDamage(0);
	assertTest(ct.getHitPoints() == 10, "Taking 0 damage leaves HP unchanged");
	ct.beRepaired(0);
	assertTest(ct.getEnergyPoints() == 9,
		"Repairing 0 still costs 1 EP (rule check)");
}

int	main(void)
{
	std::cout << BOLD YELLOW << "STARTING CLAPTRAP DESTRUCTIVE TEST SUITE" << RESET << std::endl;

	testOrthodoxCanonicalForm();
	testInitialStats();
	testNormalActions();
	testDeathAndRestrictions();
	testOverkillDamage();
	testEnergyDepletion();
	testDestructiveOverflowRepair();
	testZeroDamageAndRepair();

	std::cout << std::endl << BOLD << "=====================================" << RESET << std::endl;
	std::cout << BOLD << "TOTAL: " << g_tests_passed << "/" << g_tests_total << " tests passed." << RESET << std::endl;

	if (g_tests_passed == g_tests_total)
		std::cout << BRIGHT_GREEN << "ALL TESTS PASSED!" << RESET << std::endl;
	else
		std::cout << BRIGHT_RED << "SOME TESTS FAILED!" << RESET << std::endl;

	return (g_tests_passed != g_tests_total);
}
