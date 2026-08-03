// File: src/main.cpp
#include "../include/Bureaucrat.hpp"
#include "../include/AForm.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/PresidentialPardonForm.hpp"
#include "../include/Intern.hpp"
#include "../include/Colors.hpp"
#include <iostream>
#include <fstream>
#include <string>

// --------------------- Test Framework Helpers ---------------------

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
              << BOLD BG_MAGENTA << " " << title << " " << RESET << std::endl;
}

static bool fileContains(const std::string &filename, const std::string &expected)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        return false;
    std::string content;
    std::string line;
    while (std::getline(file, line))
    {
        content += line + "\n";
    }
    file.close();
    return content.find(expected) != std::string::npos;
}

// ----------------------------- Destructive Tests ----------------------------

void testValidFormCreation()
{
    printSection("1. Valid Form Creation via Intern");
    Intern intern;
    bool passed = true;

    AForm* s = intern.makeForm("shrubbery creation", "garden");
    if (s == NULL || s->getName() != "ShrubberyCreationForm" || s->getTarget() != "garden")
        passed = false;
    delete s;

    AForm* r = intern.makeForm("robotomy request", "Marvin");
    if (r == NULL || r->getName() != "RobotomyRequestForm" || r->getTarget() != "Marvin")
        passed = false;
    delete r;

    AForm* p = intern.makeForm("presidential pardon", "Arthur");
    if (p == NULL || p->getName() != "PresidentialPardonForm" || p->getTarget() != "Arthur")
        passed = false;
    delete p;

    assertTest(passed, "Intern creates valid forms with correct types and targets");
}

void testInvalidFormCreation()
{
    printSection("2. Invalid Form Creation Handling");
    Intern intern;
    AForm* invalid = intern.makeForm("invalid form", "target");
    
    assertTest(invalid == NULL, "Intern returns NULL for unknown form name");
    delete invalid; // Safe to delete NULL
}

void testPolymorphicExecution()
{
    printSection("3. Polymorphic Execution of Intern's Forms");
    Intern intern;
    Bureaucrat b("Boss", 1);
    bool passed = true;

    AForm* s = intern.makeForm("shrubbery creation", "poly_shrub");
    try {
        b.signForm(*s);
        b.executeForm(*s);
        if (!fileContains("poly_shrub_shrubbery", "/\\")) passed = false;
    } catch (...) { passed = false; }
    delete s;

    AForm* r = intern.makeForm("robotomy request", "poly_robot");
    try {
        b.signForm(*r);
        b.executeForm(*r);
    } catch (...) { passed = false; }
    delete r;

    AForm* p = intern.makeForm("presidential pardon", "poly_pres");
    try {
        b.signForm(*p);
        b.executeForm(*p);
    } catch (...) { passed = false; }
    delete p;

    assertTest(passed, "Forms created by intern can be signed and executed");
}

void testInternOCF()
{
    printSection("4. Intern Orthodox Canonical Form");
    Intern i1;
    Intern i2(i1);
    Intern i3;
    i3 = i1;

    AForm* f1 = i1.makeForm("robotomy request", "target1");
    AForm* f2 = i2.makeForm("robotomy request", "target2");
    AForm* f3 = i3.makeForm("robotomy request", "target3");

    bool passed = (f1 != NULL && f2 != NULL && f3 != NULL);
    assertTest(passed, "Intern OCF methods execute without crashing");

    delete f1;
    delete f2;
    delete f3;
}

void testDestructiveEdgeCases()
{
    printSection("5. Destructive Edge Cases");
    Intern intern;
    
    // Case sensitivity
    AForm* caps = intern.makeForm("Shrubbery Creation", "caps");
    assertTest(caps == NULL, "Intern is case-sensitive (rejects 'Shrubbery Creation')");
    delete caps;
    
    // Empty target
    AForm* empty_target = intern.makeForm("robotomy request", "");
    bool passed = (empty_target != NULL && empty_target->getTarget() == "");
    assertTest(passed, "Intern handles empty target string");
    delete empty_target;
    
    // Empty form name
    AForm* empty_name = intern.makeForm("", "target");
    assertTest(empty_name == NULL, "Intern rejects empty form name");
    delete empty_name;

    // Long target string
    std::string long_target(1000, 'x');
    AForm* long_form = intern.makeForm("presidential pardon", long_target);
    passed = (long_form != NULL && long_form->getTarget() == long_target);
    assertTest(passed, "Intern handles extremely long target string");
    delete long_form;
}

int main()
{
    std::cout << BOLD YELLOW << "STARTING EX03 DESTRUCTIVE TEST SUITE" << RESET << std::endl;

    testValidFormCreation();
    testInvalidFormCreation();
    testPolymorphicExecution();
    testInternOCF();
    testDestructiveEdgeCases();

    std::cout << std::endl
              << BOLD << "=====================================" << RESET << std::endl;
    std::cout << BOLD << "TOTAL: " << g_tests_passed << "/" << g_tests_total << " tests passed." << RESET << std::endl;

    if (g_tests_passed == g_tests_total)
        std::cout << BRIGHT_GREEN << "ALL TESTS PASSED!" << RESET << std::endl;
    else
        std::cout << BRIGHT_RED << "SOME TESTS FAILED!" << RESET << std::endl;

    return (g_tests_passed != g_tests_total);
}
