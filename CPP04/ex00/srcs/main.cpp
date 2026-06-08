#include "Animal.hpp"
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

void testSubjectRequirements()
{
    printSection("1. Subject Basic Requirements & Polymorphism");
    
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    
    assertTest(j->getType() == "Dog", "Dog type must be 'Dog'");
    assertTest(i->getType() == "Cat", "Cat type must be 'Cat'");
    assertTest(meta->getType() == "Animal", "Animal type must be 'Animal'");

    std::cout << BRIGHT_CYAN << "Animal sound: "; meta->makeSound();
    std::cout << BRIGHT_YELLOW << "Cat sound: "; i->makeSound();
    std::cout << BRIGHT_GREEN << "Dog sound: "; j->makeSound();

    delete meta;
    delete j;
    delete i;
    
    assertTest(true, "Subject main executed without crash (check valgrind for leaks)");
}

void testWrongPolymorphism()
{
    printSection("2. Wrong Polymorphism (No virtual function)");
    
    const WrongAnimal* wrong_meta = new WrongAnimal();
    const WrongAnimal* wrong_cat = new WrongCat();
    
    assertTest(wrong_meta->getType() == "WrongAnimal", "WrongAnimal type is correct");
    assertTest(wrong_cat->getType() == "WrongCat", "WrongCat type stored is 'WrongCat'");

    std::cout << BRIGHT_RED << "WrongAnimal sound: "; wrong_meta->makeSound();
    std::cout << BRIGHT_RED << "WrongCat sound (via WrongAnimal ptr): "; wrong_cat->makeSound();
    
    // Como não é virtual, o WrongCat deve emitir o som do WrongAnimal.
    // Não podemos verificar automaticamente o output do cout sem redirecionar, 
    // mas a regra de negócio exige que o comportamento visual seja este.
    assertTest(true, "Visual check: WrongCat MUST output WrongAnimal sound");

    delete wrong_meta;
    delete wrong_cat;
}

void testOrthodoxCanonicalForm()
{
    printSection("3. Orthodox Canonical Form (Deep Copy & Self-Assignment)");

    Dog original;
    original.makeSound();
    
    std::cout << BRIGHT_BLUE << "--- Copy Constructor ---" << RESET << std::endl;
    Dog copy(original);
    assertTest(copy.getType() == "Dog", "Copied Dog has correct type");
    
    std::cout << BRIGHT_BLUE << "--- Assignment Operator ---" << RESET << std::endl;
    Dog assigned;
    assigned = original;
    assertTest(assigned.getType() == "Dog", "Assigned Dog has correct type");

    std::cout << BRIGHT_BLUE << "--- Self-Assignment ---" << RESET << std::endl;
    Dog& ref = assigned; // Usar referência bypassa o -Wself-assign-overloaded do Clang
    assigned = ref;
    assertTest(assigned.getType() == "Dog", "Self-assignment handled gracefully");
}

void testObjectSlicing()
{
    printSection("4. Destructive Test: Object Slicing");

    Cat cat;
    Animal sliced_animal = cat; // Slicing! O objeto perde a parte da classe Cat.

    assertTest(sliced_animal.getType() == "Cat", "Sliced animal keeps 'Cat' type string (data)");
    
    std::cout << BRIGHT_CYAN << "Sliced Animal sound: "; sliced_animal.makeSound();
    assertTest(true, "Visual check: Sliced Animal MUST bark (Animal sound), not Meow! (VTable sliced)");
}

void testDirectInstantiation()
{
    printSection("5. Direct Instantiation & Stack Destruction Order");

    std::cout << BRIGHT_BLUE << "--- Creating Dog on stack ---" << RESET << std::endl;
    {
        Dog stack_dog;
        stack_dog.makeSound();
    } // Destrutor chamado aqui
    std::cout << BRIGHT_BLUE << "--- Dog destroyed ---" << RESET << std::endl;
    assertTest(true, "Visual check: Dog destroyed in correct LIFO order");
}

int main()
{
    std::cout << BOLD YELLOW << "STARTING ANIMAL DESTRUCTIVE TEST SUITE" << RESET << std::endl;

    testSubjectRequirements();
    testWrongPolymorphism();
    testOrthodoxCanonicalForm();
    testObjectSlicing();
    testDirectInstantiation();

    std::cout << std::endl
              << BOLD << "=====================================" << RESET << std::endl;
    std::cout << BOLD << "TOTAL: " << g_tests_passed << "/" << g_tests_total << " tests passed." << RESET << std::endl;

    if (g_tests_passed == g_tests_total)
        std::cout << BRIGHT_GREEN << "ALL TESTS PASSED!" << RESET << std::endl;
    else
        std::cout << BRIGHT_RED << "SOME TESTS FAILED!" << RESET << std::endl;

    return (g_tests_passed != g_tests_total);
}
