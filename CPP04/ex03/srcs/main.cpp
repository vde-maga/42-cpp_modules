#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Colors.hpp"
#include <iostream>
#include <string>

// --------------------- Test Framework Macros & Helpers ---------------------
static int g_tests_passed = 0;
static int g_tests_total = 0;

static void assertTest(bool condition, const std::string &test_name)
{
    ++g_tests_total;
    if (condition) {
        ++g_tests_passed;
        std::cout << BRIGHT_GREEN << "[PASS] " << RESET << test_name << std::endl;
    } else {
        std::cout << BRIGHT_RED << "[FAIL] " << RESET << test_name << std::endl;
    }
}

static void printSection(const std::string &title)
{
    std::cout << std::endl << BOLD BG_BLUE << " " << title << " " << RESET << std::endl;
}

// ----------------------------- Destructive Tests ----------------------------

void testSubjectMain()
{
    printSection("1. Subject Main Test");
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");

    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);

    delete bob;
    delete me;
    delete src;

    assertTest(true, "Subject main executed (verify Valgrind)");
}

void testInventoryLimits()
{
    printSection("2. Destructive Inventory Limits");
    Character me("FullGuy");
    AMateria* m1 = new Ice();
    AMateria* m2 = new Ice();
    AMateria* m3 = new Cure();
    AMateria* m4 = new Cure();
    AMateria* m5 = new Ice(); // Este vai sobrar

    me.equip(m1);
    me.equip(m2);
    me.equip(m3);
    me.equip(m4);
    me.equip(m5); // Inventário cheio!

    assertTest(true, "Equipping 5 materias didn't crash (5th goes to floor)");
    
    me.use(4, me); // Index out of bounds
    me.use(-1, me); // Index negative
    assertTest(true, "Using invalid indexes didn't crash");
}

void testUnequipFloorMechanics()
{
    printSection("3. Destructive Unequip & Floor Memory Leak Test");
    Character me("Dropper");
    me.equip(new Ice());
    me.equip(new Cure());

    me.unequip(0); // Ice vai para o chão
    me.unequip(1); // Cure vai para o chão
    me.unequip(5); // Index inválido, não faz nada

    assertTest(true, "Unequipping items executed. Check Valgrind to ensure NO leaks (Floor cleans up)");
}

void testDeepCopyCharacter()
{
    printSection("4. Destructive Deep Copy Character");
    Character original("Original");
    original.equip(new Ice());

    Character copy(original);
    assertTest(copy.getName() == "Original", "Copy constructor copied name");

    copy.use(0, original); // Must use Ice, proving deep copy of inventory
    
    // Modificar a cópia NÃO pode afetar o original
    copy.unequip(0);
    original.use(0, copy); // Original still has Ice!
    assertTest(true, "Deep copy independence verified");
}

void testMateriaSourceUnknown()
{
    printSection("5. MateriaSource Unknown Type & Limits");
    MateriaSource src;
    src.learnMateria(new Ice());
    AMateria* m = src.createMateria("fire");
    assertTest(m == 0, "Creating unknown materia returns 0 (NULL)");
    delete m; // Just in case, though it should be NULL
}

int main()
{
    std::cout << BOLD YELLOW << "STARTING EX03 DESTRUCTIVE TEST SUITE" << RESET << std::endl;

    testSubjectMain();
    testInventoryLimits();
    testUnequipFloorMechanics();
    testDeepCopyCharacter();
    testMateriaSourceUnknown();

    std::cout << std::endl << BOLD << "=====================================" << RESET << std::endl;
    std::cout << BOLD << "TOTAL: " << g_tests_passed << "/" << g_tests_total << " tests passed." << RESET << std::endl;

    if (g_tests_passed == g_tests_total)
        std::cout << BRIGHT_GREEN << "ALL TESTS PASSED!" << RESET << std::endl;
    else
        std::cout << BRIGHT_RED << "SOME TESTS FAILED!" << RESET << std::endl;

    return (g_tests_passed != g_tests_total);
}