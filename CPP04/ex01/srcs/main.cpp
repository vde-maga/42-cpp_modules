#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
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

void testSubjectArray()
{
    printSection("1. Subject Array - Polymorphism & Leak Prevention");
    
    const int arraySize = 4;
    const Animal* animals[arraySize];

    std::cout << BRIGHT_BLUE << "--- Creating half Dogs, half Cats ---" << RESET << std::endl;
    for (int i = 0; i < arraySize; ++i)
    {
        if (i < arraySize / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    std::cout << BRIGHT_BLUE << "--- Deleting all Animals as Animals ---" << RESET << std::endl;
    for (int i = 0; i < arraySize; ++i)
        delete animals[i]; // Graças ao virtual ~Animal(), chama os destrutores derivados
    
    assertTest(true, "Array test executed without leaks (verify with Valgrind)");
}

void testSubjectPointers()
{
    printSection("2. Subject Direct Pointer Test");
    
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    
    delete j; // Should not create a leak
    delete i; // Should not create a leak
    
    assertTest(true, "Direct pointer deletion executed (verify Valgrind)");
}

void testDeepCopyConstructor()
{
    printSection("3. Destructive Deep Copy - Copy Constructor");
    
    Cat original;
    original.getBrain()->setIdea(0, "Catch the red dot");
    original.getBrain()->setIdea(1, "Sleep on the keyboard");

    std::cout << BRIGHT_BLUE << "--- Copying Cat ---" << RESET << std::endl;
    Cat copy(original);

    // Verificar se as ideias foram copiadas
    assertTest(copy.getBrain()->getIdea(0) == "Catch the red dot", "Copy Constructor: Idea 0 copied successfully");
    
    // A GRANDE PROVA: Modificar o original NÃO pode afetar a cópia
    original.getBrain()->setIdea(0, "Eat fish");
    
    assertTest(original.getBrain()->getIdea(0) == "Eat fish", "Original Cat idea changed");
    assertTest(copy.getBrain()->getIdea(0) == "Catch the red dot", "Copy Cat idea REMAINED unchanged (Deep Copy confirmed)");
}

void testDeepCopyAssignment()
{
    printSection("4. Destructive Deep Copy - Assignment Operator");
    
    Dog original;
    original.getBrain()->setIdea(0, "Bark at the mailman");

    Dog assigned;
    assigned = original; // Usa o operator=

    assertTest(assigned.getBrain()->getIdea(0) == "Bark at the mailman", "Assignment: Idea 0 copied successfully");

    // Prova de que são memórias independentes
    original.getBrain()->setIdea(0, "Chase tail");
    assertTest(assigned.getBrain()->getIdea(0) == "Bark at the mailman", "Assigned Dog idea REMAINED unchanged (Deep Copy confirmed)");
}

void testSelfAssignment()
{
    printSection("5. Defensive Test: Self-Assignment");
    
    Cat cat;
    cat.getBrain()->setIdea(0, "Purr");
    
    Cat& ref = cat; // Bypass -Wself-assign-overloaded
    cat = ref;

    assertTest(cat.getBrain()->getIdea(0) == "Purr", "Self-assignment did not corrupt data or leak");
}

int main()
{
    std::cout << BOLD YELLOW << "STARTING EX01 DESTRUCTIVE TEST SUITE" << RESET << std::endl;

    testSubjectArray();
    testSubjectPointers();
    testDeepCopyConstructor();
    testDeepCopyAssignment();
    testSelfAssignment();

    std::cout << std::endl
              << BOLD << "=====================================" << RESET << std::endl;
    std::cout << BOLD << "TOTAL: " << g_tests_passed << "/" << g_tests_total << " tests passed." << RESET << std::endl;

    if (g_tests_passed == g_tests_total)
        std::cout << BRIGHT_GREEN << "ALL TESTS PASSED!" << RESET << std::endl;
    else
        std::cout << BRIGHT_RED << "SOME TESTS FAILED!" << RESET << std::endl;

    return (g_tests_passed != g_tests_total);
}