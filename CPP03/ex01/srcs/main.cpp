#include "ScavTrap.hpp" // Inclui indiretamente o ClapTrap
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
			  << BOLD BG_BLUE << " " << title << " "
			  << RESET << std::endl;
}

// ----------------------------- Destructive Tests ----------------------------

void testConstructionDestruction()
{
	printSection("1. Construction & Destruction Chaining");
	std::cout << BRIGHT_YELLOW << "--- Creating ScavTrap 'Chainer' ---" << RESET << std::endl;
	{
		ScavTrap chainer("Chainer");
	} // Destrutor chamado aqui
	std::cout << BRIGHT_YELLOW << "--- ScavTrap 'Chainer' destroyed ---" << RESET << std::endl;
	assertTest(true, "Visual check: ClapTrap built first, destroyed last");
}

void testScavTrapInitialStats()
{
	printSection("2. ScavTrap Initial Stats (Subject Rules)");

	ScavTrap st("Stats");

	assertTest(st.getHitPoints() == 100, "ScavTrap Initial HP must be 100");
	assertTest(st.getEnergyPoints() == 50, "ScavTrap Initial EP must be 50");
	assertTest(st.getAttackDamage() == 20, "ScavTrap Initial AD must be 20");
}

void testScavTrapNormalActions()
{
	printSection("3. ScavTrap Normal Actions & Energy Drain");

	ScavTrap st("Normal");

	st.attack("Target1");
	assertTest(st.getEnergyPoints() == 49, "ScavTrap attack costs 1 EP");

	st.beRepaired(20);
	assertTest(st.getEnergyPoints() == 48, "ScavTrap repair costs 1 EP");
	assertTest(st.getHitPoints() == 120, "ScavTrap repair adds HP correctly");
}

void testScavTrapDeathAndRestrictions()
{
	printSection("4. ScavTrap Death & Action Restrictions");
    
	ScavTrap st("Dead");
	st.takeDamage(100);
    
	assertTest(st.getHitPoints() == 0, "ScavTrap taking full damage kills it");
    
	st.attack("Ghost"); 
	assertTest(st.getEnergyPoints() == 50, "Dead ScavTrap does NOT spend EP on failed attack");
    
	st.beRepaired(10); 
	assertTest(st.getHitPoints() == 0, "Dead ScavTrap cannot be repaired");
}

void testScavTrapOverkill()
{
	printSection("5. ScavTrap Overkill (No Underflow)");

	ScavTrap st("Overkill");
	st.takeDamage(9999);

	assertTest(st.getHitPoints() == 0, "ScavTrap HP cannot go below 0 on massive damage");
}

void testScavTrapEnergyDepletion()
{
	printSection("6. ScavTrap Energy Depletion (50 Actions Max)");

	ScavTrap st("Tired");

	for (int i = 0; i < 50; ++i) // Pré-incremento
		st.attack("Dummy");

	assertTest(st.getEnergyPoints() == 0, "ScavTrap EP reaches 0 after 50 attacks");

	st.attack("Exhausted");
	st.beRepaired(1);

	assertTest(st.getHitPoints() == 100, "No EP means no actions at all");
}

void testScavTrapOverflowRepair()
{
	printSection("7. ScavTrap Destructive Overflow Test (MAX UINT)");

	ScavTrap st("Overflow");
	const unsigned int max_uint = static_cast<unsigned int>(-1);

	st.beRepaired(max_uint);
	assertTest(st.getHitPoints() == max_uint, "ScavTrap Repair to MAX_UINT succeeds safely");

	st.beRepaired(1);
	assertTest(st.getHitPoints() == max_uint, "ScavTrap HP caps at MAX_UINT instead of overflowing");
}

void testGuardGate()
{
	printSection("8. Special Ability: GuardGate");

	ScavTrap st("Guard");
	st.guardGate();
	assertTest(true, "GuardGate executed without crash");
}

void testClapTrapIndependence()
{
	printSection("9. ClapTrap Still Works Independently");

	ClapTrap ct("Alone");
	ct.attack("Target");
	ct.takeDamage(5);
	ct.beRepaired(3);

	assertTest(ct.getHitPoints() == 8, "ClapTrap logic remains intact (8 HP)");
}

int main()
{
	std::cout << BOLD YELLOW << "STARTING SCAVTRAP DESTRUCTIVE TEST SUITE" << RESET << std::endl;

	testConstructionDestruction();
	testScavTrapInitialStats();
	testScavTrapNormalActions();
	testScavTrapDeathAndRestrictions();
	testScavTrapOverkill();
	testScavTrapEnergyDepletion();
	testScavTrapOverflowRepair();
	testGuardGate();
	testClapTrapIndependence();

	std::cout << std::endl
			  << BOLD << "=====================================" << RESET << std::endl;
	std::cout << BOLD << "TOTAL: " << g_tests_passed << "/" << g_tests_total << " tests passed." << RESET << std::endl;

	if (g_tests_passed == g_tests_total)
		std::cout << BRIGHT_GREEN << "ALL TESTS PASSED!" << RESET << std::endl;
	else
		std::cout << BRIGHT_RED << "SOME TESTS FAILED!" << RESET << std::endl;

	return (g_tests_passed != g_tests_total);
}
