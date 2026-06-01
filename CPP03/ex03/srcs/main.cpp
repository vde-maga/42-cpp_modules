#include "DiamondTrap.hpp"
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

void testDiamondConstructionDestruction()
{
	printSection("1. Diamond Construction & Single ClapTrap Instance (Virtual Inheritance)");
	std::cout << BRIGHT_YELLOW << "--- Creating DiamondTrap 'Chainer' ---" << RESET << std::endl;
	{
		DiamondTrap chainer("Chainer");
		chainer.whoAmI();
	} // Deve chamar apenas UM destrutor de ClapTrap
	std::cout << BRIGHT_YELLOW << "--- DiamondTrap 'Chainer' destroyed ---" << RESET << std::endl;
	assertTest(true, "Visual check: ClapTrap constructed/destroyed ONCE");
}

void testDiamondInitialStats()
{
	printSection("2. DiamondTrap Initial Stats (Subject Rules)");

	DiamondTrap dt("Stats");

	assertTest(dt.getHitPoints() == 100, "Diamond Initial HP must be 100 (Frag)");
	assertTest(dt.getEnergyPoints() == 50, "Diamond Initial EP must be 50 (Scav)");
	assertTest(dt.getAttackDamage() == 30, "Diamond Initial AD must be 30 (Frag)");
}

void testDiamondNamingWhoAmI()
{
	printSection("3. DiamondTrap Naming & whoAmI (Shadowing & Suffix)");

	DiamondTrap dt("Boss");

	// Testar se a names estão corretas e separadas
	assertTest(dt.getName() == "Boss_clap_name", "Diamond ClapTrap::name has '_clap_name' suffix");
	// Como o _name é privado na Diamond, só podemos verificá-lo via whoAmI output.
	dt.whoAmI(); // Apenas verificação visual de que não há ambiguidade
	assertTest(true, "whoAmI executed without ambiguity crash");
}

void testDiamondAttackSemantics()
{
	printSection("4. DiamondTrap Attack Uses ScavTrap Semantics");

	DiamondTrap dt("Attacker");

	dt.attack("Target1");
	assertTest(dt.getEnergyPoints() == 49, "Diamond attack costs 1 EP (Scav rules)");
	// Dano já foi verificado nos stats, e a mensagem deve ser de ScavTrap
}

void testDiamondDeathAndRestrictions()
{
	printSection("5. DiamondTrap Death & Action Restrictions");

	DiamondTrap dt("Dead");
	dt.takeDamage(100);

	assertTest(dt.getHitPoints() == 0, "Diamond taking full damage kills it");

	dt.attack("Ghost");
	assertTest(dt.getEnergyPoints() == 50, "Dead Diamond cannot spend EP to attack");

	dt.beRepaired(10);
	assertTest(dt.getHitPoints() == 0, "Dead Diamond cannot be repaired");
}

void testDiamondOverkill()
{
	printSection("6. DiamondTrap Overkill (No Underflow)");

	DiamondTrap dt("Overkill");
	dt.takeDamage(9999);

	assertTest(dt.getHitPoints() == 0, "Diamond HP cannot go below 0 on massive damage");
}

void testDiamondEnergyDepletion()
{
	printSection("7. DiamondTrap Energy Depletion (50 Actions Max - Scav Rules)");

	DiamondTrap dt("Tired");

	for (int i = 0; i < 50; ++i) // Pré-incremento
		dt.attack("Dummy");

	assertTest(dt.getEnergyPoints() == 0, "Diamond EP reaches 0 after 50 attacks");

	dt.attack("Exhausted");
	dt.beRepaired(1);

	assertTest(dt.getHitPoints() == 100, "No EP means no actions at all");
}

void testDiamondOverflowRepair()
{
	printSection("8. DiamondTrap Destructive Overflow Test (MAX UINT)");

	DiamondTrap dt("Overflow");
	const unsigned int max_uint = static_cast<unsigned int>(-1);

	dt.beRepaired(max_uint);
	assertTest(dt.getHitPoints() == max_uint, "Diamond Repair to MAX_UINT succeeds safely");

	dt.beRepaired(1);
	assertTest(dt.getHitPoints() == max_uint, "Diamond HP caps at MAX_UINT instead of overflowing");
}

void testDiamondSpecialAbilities()
{
	printSection("9. Special Abilities From Both Parents");

	DiamondTrap dt("Special");

	dt.highFivesGuys(); // De FragTrap
	dt.guardGate();		// De ScavTrap

	assertTest(true, "Both special abilities executed without crash");
}

void testDiamondCopyAssignment()
{
	printSection("10. DiamondTrap Copy & Assignment Integrity");

	DiamondTrap original("Original");
	original.takeDamage(20);  // HP = 80, EP continua 50
	original.attack("Dummy"); // EP desce de 50 para 49

	DiamondTrap copy(original);
	assertTest(copy.getHitPoints() == 80, "Copy Constructor: HP matches original");
	assertTest(copy.getEnergyPoints() == 49, "Copy Constructor: EP matches original");

	DiamondTrap assigned("Assigned");
	assigned = original;
	assertTest(assigned.getHitPoints() == 80, "Assignment Operator: HP matches original");
	assertTest(assigned.getEnergyPoints() == 49, "Assignment Operator: EP matches original");
}

int main()
{
	std::cout << BOLD YELLOW << "STARTING DIAMONDTRAP DESTRUCTIVE TEST SUITE" << RESET << std::endl;

	testDiamondConstructionDestruction();
	testDiamondInitialStats();
	testDiamondNamingWhoAmI();
	testDiamondAttackSemantics();
	testDiamondDeathAndRestrictions();
	testDiamondOverkill();
	testDiamondEnergyDepletion();
	testDiamondOverflowRepair();
	testDiamondSpecialAbilities();
	testDiamondCopyAssignment();

	std::cout << std::endl
			  << BOLD << "=====================================" << RESET << std::endl;
	std::cout << BOLD << "TOTAL: " << g_tests_passed << "/" << g_tests_total << " tests passed." << RESET << std::endl;

	if (g_tests_passed == g_tests_total)
		std::cout << BRIGHT_GREEN << "ALL TESTS PASSED!" << RESET << std::endl;
	else
		std::cout << BRIGHT_RED << "SOME TESTS FAILED!" << RESET << std::endl;

	return (g_tests_passed != g_tests_total);
}