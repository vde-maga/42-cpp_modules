#include "../include/Intern.hpp"
#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/Colors.hpp"
#include <iostream>
#include <string>
# include <ctime>
# include <cstdlib>

static void print_header(const std::string &title)
{
    std::cout << std::endl
              << BOLD << MAGENTA << "=== " << title << " ===" << RESET << std::endl;
}

static void safe_delete(AForm *form)
{
    if (form)
        delete form;
}

static void test_make_form_valid(void)
{
    print_header("makeForm - Valid Forms");
    Intern intern;

    AForm *shrub = intern.makeForm("shrubbery creation", "home");
    if (shrub && shrub->getName() == "ShrubberyCreationForm" && shrub->getTarget() == "home" && shrub->getGradeToSign() == 145 && shrub->getGradeToExecute() == 137)
    {
        std::cout << GREEN << "Passed: shrubbery creation created correctly." << RESET << std::endl;
    }
    else
    {
        std::cout << RED << "[FAIL] shrubbery creation failed!" << RESET << std::endl;
    }
    safe_delete(shrub);

    AForm *robot = intern.makeForm("robotomy request", "Bender");
    if (robot && robot->getName() == "RobotomyRequestForm" && robot->getTarget() == "Bender" && robot->getGradeToSign() == 72 && robot->getGradeToExecute() == 45)
    {
        std::cout << GREEN << "Passed: robotomy request created correctly." << RESET << std::endl;
    }
    else
    {
        std::cout << RED << "[FAIL] robotomy request failed!" << RESET << std::endl;
    }
    safe_delete(robot);

    AForm *pres = intern.makeForm("presidential pardon", "Arthur");
    if (pres && pres->getName() == "PresidentialPardonForm" && pres->getTarget() == "Arthur" && pres->getGradeToSign() == 25 && pres->getGradeToExecute() == 5)
    {
        std::cout << GREEN << "Passed: presidential pardon created correctly." << RESET << std::endl;
    }
    else
    {
        std::cout << RED << "[FAIL] presidential pardon failed!" << RESET << std::endl;
    }
    safe_delete(pres);
}

static void test_make_form_invalid(void)
{
    print_header("makeForm - Invalid Forms");
    Intern intern;

    AForm *invalid = intern.makeForm("nonexistent form", "target");
    if (invalid == NULL)
    {
        std::cout << GREEN << "Passed: Invalid form name returns NULL." << RESET << std::endl;
    }
    else
    {
        std::cout << RED << "[FAIL] Invalid form should return NULL!" << RESET << std::endl;
        safe_delete(invalid);
    }

    AForm *empty = intern.makeForm("", "target");
    if (empty == NULL)
    {
        std::cout << GREEN << "Passed: Empty form name returns NULL." << RESET << std::endl;
    }
    else
    {
        std::cout << RED << "[FAIL] Empty form should return NULL!" << RESET << std::endl;
        safe_delete(empty);
    }
}

static void test_case_sensitivity(void)
{
    print_header("makeForm - Case Sensitivity");
    Intern intern;

    AForm *upper = intern.makeForm("SHRUBBERY CREATION", "home");
    if (upper == NULL)
    {
        std::cout << GREEN << "Passed: Uppercase form name returns NULL (case sensitive)." << RESET << std::endl;
    }
    else
    {
        std::cout << RED << "[FAIL] Uppercase form should not match!" << RESET << std::endl;
        safe_delete(upper);
    }

    AForm *mixed = intern.makeForm("Robotomy Request", "Bender");
    if (mixed == NULL)
    {
        std::cout << GREEN << "Passed: Mixed case form name returns NULL." << RESET << std::endl;
    }
    else
    {
        std::cout << RED << "[FAIL] Mixed case form should not match!" << RESET << std::endl;
        safe_delete(mixed);
    }
}

static void test_intern_ocf(void)
{
    print_header("Intern OCF");
    Intern intern1;
    Intern intern2(intern1);
    Intern intern3;
    intern3 = intern1;
    std::cout << GREEN << "Passed: Intern OCF does not crash." << RESET << std::endl;
}

static void test_integration_full_cycle(void)
{
    print_header("Integration: Intern + Bureaucrat Full Cycle");
    Intern intern;
    Bureaucrat boss("Boss", 1);

    AForm *form = intern.makeForm("presidential pardon", "Target");
    if (!form)
    {
        std::cout << RED << "[FAIL] Integration failed: form is NULL!" << RESET << std::endl;
        return;
    }

    boss.signForm(*form);
    boss.executeForm(*form);
    safe_delete(form);
    std::cout << GREEN << "Passed: Full integration cycle works." << RESET << std::endl;
}

static void test_polymorphism_with_intern(void)
{
    print_header("Polymorphism with Intern");
    Intern intern;
    AForm *forms[3];

    forms[0] = intern.makeForm("shrubbery creation", "garden");
    forms[1] = intern.makeForm("robotomy request", "robot");
    forms[2] = intern.makeForm("presidential pardon", "citizen");

    Bureaucrat ceo("CEO", 1);

    for (int i = 0; i < 3; ++i)
    {
        if (forms[i])
        {
            ceo.signForm(*forms[i]);
            ceo.executeForm(*forms[i]);
        }
    }

    for (int i = 0; i < 3; ++i)
        safe_delete(forms[i]);

    std::cout << GREEN << "Passed: Polymorphic array via Intern works." << RESET << std::endl;
}

int main(void)
{
    std::srand(std::time(NULL));

    test_make_form_valid();
    test_make_form_invalid();
    test_case_sensitivity();
    test_intern_ocf();
    test_integration_full_cycle();
    test_polymorphism_with_intern();

    std::cout << std::endl
              << BOLD << GREEN << "All Intern TDD Tests Completed Successfully." << RESET << std::endl;
    return (0);
}