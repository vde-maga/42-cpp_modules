#include "../include/Bureaucrat.hpp"
#include "../include/Colors.hpp"
#include <iostream>
#include <string>

static void print_header(const std::string &title)
{
    std::cout << std::endl
              << BOLD << MAGENTA << "=== " << title << " ===" << RESET << std::endl;
}

static void test_construction(void)
{
    print_header("Construction & Boundary Exceptions");

    try
    {
        Bureaucrat default_b;
        Bureaucrat high("Alice", Bureaucrat::HIGHEST_GRADE);
        Bureaucrat low("Bob", Bureaucrat::LOWEST_GRADE);
        std::cout << GREEN << "Valid constructions successful." << RESET << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << RED << "[FAIL] Unexpected exception in valid construction: " << e.what() << RESET << std::endl;
    }

    // Teste Extremo: Grau 0 (Muito alto)
    try
    {
        Bureaucrat invalid_high("Charlie", 0);
        std::cout << RED << "[FAIL] Failed to catch exception for grade 0!" << RESET << std::endl;
    }
    catch (Bureaucrat::GradeTooHighException &e)
    {
        std::cout << GREEN << "Passed: Caught expected exception for grade 0." << RESET << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << RED << "[FAIL] Caught wrong exception type for grade 0: " << e.what() << RESET << std::endl;
    }

    // Teste Extremo: Grau 151 (Muito baixo)
    try
    {
        Bureaucrat invalid_low("Dave", 151);
        std::cout << RED << "[FAIL] Failed to catch exception for grade 151!" << RESET << std::endl;
    }
    catch (Bureaucrat::GradeTooLowException &e)
    {
        std::cout << GREEN << "Passed: Caught expected exception for grade 151." << RESET << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << RED << "[FAIL] Caught wrong exception type for grade 151: " << e.what() << RESET << std::endl;
    }
}

static void test_modifiers(void)
{
    print_header("Modifiers & Edge Cases");

    Bureaucrat promoter("Promoter", 2);
    std::cout << "Before increment: " << promoter << std::endl;
    promoter.incrementGrade();
    std::cout << "After increment (Expected Grade 1): " << promoter << std::endl;

    try
    {
        promoter.incrementGrade(); // Deve falhar (já é 1)
        std::cout << RED << "[FAIL] Failed to catch exception on increment at grade 1!" << RESET << std::endl;
    }
    catch (Bureaucrat::GradeTooHighException &e)
    {
        std::cout << GREEN << "Passed: Blocked increment at maximum grade." << RESET << std::endl;
    }

    Bureaucrat demoted("Demoted", 149);
    std::cout << "Before decrement: " << demoted << std::endl;
    demoted.decrementGrade();
    std::cout << "After decrement (Expected Grade 150): " << demoted << std::endl;

    try
    {
        demoted.decrementGrade(); // Deve falhar (já é 150)
        std::cout << RED << "[FAIL] Failed to catch exception on decrement at grade 150!" << RESET << std::endl;
    }
    catch (Bureaucrat::GradeTooLowException &e)
    {
        std::cout << GREEN << "Passed: Blocked decrement at lowest grade." << RESET << std::endl;
    }
}

static void test_canonical_form(void)
{
    print_header("OCF (Copy & Assignment)");

    Bureaucrat original("Original", 42);
    Bureaucrat copy_target("Target", 100);

    std::cout << "Original: " << original << std::endl;
    std::cout << "Target Before: " << copy_target << std::endl;

    copy_target = original;

    std::cout << "Target After Assignment: " << copy_target << std::endl;
    // Validação Semântica: O nome DEVE permanecer "Target" (const),
    // mas o grau deve ser atualizado para 42.

    Bureaucrat direct_copy(original);
    std::cout << "Direct Copy Constructor: " << direct_copy << std::endl;
}

int main(void)
{
    test_construction();
    test_modifiers();
    test_canonical_form();

    std::cout << std::endl
              << BOLD << GREEN << "All TDD Tests Completed Successfully." << RESET << std::endl;
    return (0);
}