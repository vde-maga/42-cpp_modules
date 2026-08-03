// File: src/main.cpp
#include "../include/Bureaucrat.hpp"
#include "../include/AForm.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/PresidentialPardonForm.hpp"
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

static bool fileExists(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    return file.good();
}

// ----------------------------- Destructive Tests ----------------------------

void testOrthodoxCanonicalForm()
{
    printSection("1. Orthodox Canonical Form (Concrete Forms)");

    ShrubberyCreationForm s1("home");
    ShrubberyCreationForm s2(s1);
    ShrubberyCreationForm s3;
    s3 = s1;

    assertTest(s1.getTarget() == "home" && s2.getTarget() == "home" && s3.getTarget() == "home", "Shrubbery OCF (Copy & Assignment) preserves target");
    assertTest(s1.getGradeToSign() == 145 && s1.getGradeToExecute() == 137, "Shrubbery grades correct (145/137)");

    RobotomyRequestForm r1("robot");
    RobotomyRequestForm r2(r1);
    RobotomyRequestForm r3;
    r3 = r1;

    assertTest(r1.getTarget() == "robot" && r2.getTarget() == "robot" && r3.getTarget() == "robot", "Robotomy OCF (Copy & Assignment) preserves target");
    assertTest(r1.getGradeToSign() == 72 && r1.getGradeToExecute() == 45, "Robotomy grades correct (72/45)");

    PresidentialPardonForm p1("pres");
    PresidentialPardonForm p2(p1);
    PresidentialPardonForm p3;
    p3 = p1;

    assertTest(p1.getTarget() == "pres" && p2.getTarget() == "pres" && p3.getTarget() == "pres", "Presidential OCF (Copy & Assignment) preserves target");
    assertTest(p1.getGradeToSign() == 25 && p1.getGradeToExecute() == 5, "Presidential grades correct (25/5)");
}

void testSuccessfulExecutions()
{
    printSection("2. Successful Execution via Bureaucrat");

    Bureaucrat president("Zaphod", 1);

    // Shrubbery
    ShrubberyCreationForm sForm("garden");
    president.signForm(sForm);
    president.executeForm(sForm);
    assertTest(fileExists("garden_shrubbery") && fileContains("garden_shrubbery", "/\\"), "Shrubbery executed: File created with ASCII trees");

    // Robotomy
    RobotomyRequestForm rForm("Marvin");
    president.signForm(rForm);
    bool no_throw = true;
    try
    {
        president.executeForm(rForm);
    }
    catch (...)
    {
        no_throw = false;
    }
    assertTest(no_throw, "Robotomy executed without throwing exceptions");

    // Presidential
    PresidentialPardonForm pForm("Arthur");
    president.signForm(pForm);
    no_throw = true;
    try
    {
        president.executeForm(pForm);
    }
    catch (...)
    {
        no_throw = false;
    }
    assertTest(no_throw, "Presidential executed without throwing exceptions");
}

void testUnsignedFormExecution()
{
    printSection("3. Execution of Unsigned Forms (Defensive)");

    Bureaucrat b("Exec", 1);
    ShrubberyCreationForm sForm("unsigned");
    b.executeForm(sForm); // Should print error, not throw

    assertTest(!fileExists("unsigned_shrubbery"), "Unsigned Shrubbery did not create file");

    bool caught_exception = false;
    try
    {
        sForm.execute(b);
    }
    catch (const AForm::FormNotSignedException &e)
    {
        caught_exception = true;
    }
    catch (...)
    {
    }
    assertTest(caught_exception, "Direct execute() on unsigned form throws FormNotSignedException");
}

void testGradeTooLowExecution()
{
    printSection("4. Grade Too Low Execution (Defensive)");

    Bureaucrat signer("Signer", 1);
    Bureaucrat executor("LowExec", 150);

    PresidentialPardonForm pForm("Target");
    signer.signForm(pForm);

    executor.executeForm(pForm); // Should print error

    bool caught_exception = false;
    try
    {
        pForm.execute(executor);
    }
    catch (const AForm::GradeTooLowException &e)
    {
        caught_exception = true;
    }
    catch (...)
    {
    }
    assertTest(caught_exception, "Direct execute() with low grade throws GradeTooLowException");
}

void testPolymorphismAndDestruction()
{
    printSection("5. Polymorphism & Virtual Destructors");

    Bureaucrat b("Boss", 1);
    AForm *forms[3];
    forms[0] = new ShrubberyCreationForm("poly_shrub");
    forms[1] = new RobotomyRequestForm("poly_robot");
    forms[2] = new PresidentialPardonForm("poly_pres");

    bool all_executed = true;
    for (int i = 0; i < 3; ++i)
    {
        try
        {
            b.signForm(*forms[i]);
            b.executeForm(*forms[i]);
        }
        catch (...)
        {
            all_executed = false;
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        delete forms[i];
    }

    assertTest(all_executed, "Polymorphic array of AForm* executed successfully");
    assertTest(fileExists("poly_shrub_shrubbery"), "Polymorphic Shrubbery created file correctly");
}

void testDestructiveEdgeCases()
{
    printSection("6. Destructive Edge Cases & UB Prevention");

    // Overwriting existing file
    {
        Bureaucrat b("Writer", 1);
        ShrubberyCreationForm s("overwrite");
        b.signForm(s);
        b.executeForm(s); // First write

        ShrubberyCreationForm s2("overwrite");
        b.signForm(s2);
        b.executeForm(s2); // Second write

        assertTest(fileExists("overwrite_shrubbery"), "Overwriting existing shrubbery file succeeds without crash");
    }

    // Spaces in target
    {
        Bureaucrat b("Writer", 1);
        ShrubberyCreationForm s("space target");
        b.signForm(s);
        b.executeForm(s);
        assertTest(fileExists("space target_shrubbery"), "Shrubbery with spaces in target creates valid filename");
    }

    // Execute multiple times
    {
        Bureaucrat b("Multi", 1);
        RobotomyRequestForm r("multi_robot");
        b.signForm(r);
        bool no_throw = true;
        for (int i = 0; i < 10; ++i)
        {
            try
            {
                b.executeForm(r);
            }
            catch (...)
            {
                no_throw = false;
            }
        }
        assertTest(no_throw, "Executing Robotomy multiple times does not cause crashes or UB");
    }
}

int main()
{
    std::cout << BOLD YELLOW << "STARTING EX02 DESTRUCTIVE TEST SUITE" << RESET << std::endl;

    testOrthodoxCanonicalForm();
    testSuccessfulExecutions();
    testUnsignedFormExecution();
    testGradeTooLowExecution();
    testPolymorphismAndDestruction();
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
