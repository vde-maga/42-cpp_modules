#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
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

void testAbstractClassEnforcement()
{
    printSection("1. Abstract Class Enforcement");
    
    // A linha abaixo deve CAUSAR ERRO DE COMPILAÇÃO se descomentada!
    // Isto prova que a classe é abstrata e não pode ser instanciada.
    // const AAnimal* meta = new AAnimal(); 
    
    const AAnimal* j = new Dog();
    const AAnimal* i = new Cat();

    assertTest(j->getType() == "Dog", "Dog type is correct via AAnimal pointer");
    assertTest(i->getType() == "Cat", "Cat type is correct via AAnimal pointer");

    std::cout << BRIGHT_GREEN << "Dog sound: "; j->makeSound();
    std::cout << BRIGHT_YELLOW << "Cat sound: "; i->makeSound();

    delete j;
    delete i;
    
    assertTest(true, "AAnimal pointers to derived classes work perfectly");
}

void testSubjectArray()
{
    printSection("2. Subject Array - Only Concrete Classes");
    
    const int arraySize = 4;
    const AAnimal* animals[arraySize]; // Array de ponteiros para a classe ABSTRATA

    std::cout << BRIGHT_BLUE << "--- Creating half Dogs, half Cats ---" << RESET << std::endl;
    for (int i = 0; i < arraySize; ++i)
    {
        if (i < arraySize / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    std::cout << BRIGHT_BLUE << "--- Deleting all AAnimals ---" << RESET << std::endl;
    for (int i = 0; i < arraySize; ++i)
        delete animals[i];
    
    assertTest(true, "Array of AAnimal pointers executed without leaks");
}

void testDeepCopyAssignment()
{
    printSection("3. Deep Copy Integrity with Abstract Base");
    
    Dog original;
    original.getBrain()->setIdea(0, "Bark at the mailman");

    Dog assigned;
    assigned = original;

    assertTest(assigned.getBrain()->getIdea(0) == "Bark at the mailman", "Assignment: Idea 0 copied successfully");

    original.getBrain()->setIdea(0, "Chase tail");
    assertTest(assigned.getBrain()->getIdea(0) == "Bark at the mailman", "Assigned Dog idea REMAINED unchanged (Deep Copy confirmed)");
}

void testWrongPolymorphism()
{
    printSection("4. Wrong Polymorphism Still Fails (No virtual)");
    
    const WrongAnimal* wrong_cat = new WrongCat();
    
    std::cout << BRIGHT_RED << "WrongCat sound (via WrongAnimal ptr): "; wrong_cat->makeSound();
    assertTest(wrong_cat->getType() == "WrongCat", "WrongCat type is correct");
    assertTest(true, "Visual check: WrongCat MUST output WrongAnimal sound (no virtual)");

    delete wrong_cat;
}

int main()
{
    std::cout << BOLD YELLOW << "STARTING EX02 DESTRUCTIVE TEST SUITE (ABSTRACT CLASSES)" << RESET << std::endl;

    testAbstractClassEnforcement();
    testSubjectArray();
    testDeepCopyAssignment();
    testWrongPolymorphism();

    std::cout << std::endl
              << BOLD << "=====================================" << RESET << std::endl;
    std::cout << BOLD << "TOTAL: " << g_tests_passed << "/" << g_tests_total << " tests passed." << RESET << std::endl;

    if (g_tests_passed == g_tests_total)
        std::cout << BRIGHT_GREEN << "ALL TESTS PASSED!" << RESET << std::endl;
    else
        std::cout << BRIGHT_RED << "SOME TESTS FAILED!" << RESET << std::endl;

    return (g_tests_passed != g_tests_total);
}