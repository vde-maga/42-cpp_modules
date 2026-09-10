#include "../include/Bureaucrat.hpp"
#include "../include/Form.hpp"
#include "../include/Colors.hpp"
#include <iostream>
#include <string>

static void print_header(const std::string &title)
{
    std::cout << std::endl
              << BOLD << MAGENTA << "=== " << title << " ===" << RESET << std::endl;
}

static void test_form_construction(void)
{
    print_header("Form Construction & Boundary Exceptions");

    try
    {
        Form default_f;
        Form high("Tax Return", 1, 1);
        Form low("Shopping List", 150, 150);
        std::cout << GREEN << "Valid constructions successful." << RESET << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << RED << "[FAIL] Unexpected exception in valid construction: " << e.what() << RESET << std::endl;
    }

    // Teste Extremo: Grau de assinatura 0 (Muito alto)
    try
    {
        Form invalid_high("Invalid High", 0, 50);
        std::cout << RED << "[FAIL] Failed to catch exception for sign grade 0!" << RESET << std::endl;
    }
    catch (Form::GradeTooHighException &e)
    {
        std::cout << GREEN << "Passed: Caught expected exception for sign grade 0." << RESET << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << RED << "[FAIL] Caught wrong exception type for sign grade 0: " << e.what() << RESET << std::endl;
    }

    // Teste Extremo: Grau de execução 151 (Muito baixo)
    try
    {
        Form invalid_low("Invalid Low", 50, 151);
        std::cout << RED << "[FAIL] Failed to catch exception for execute grade 151!" << RESET << std::endl;
    }
    catch (Form::GradeTooLowException &e)
    {
        std::cout << GREEN << "Passed: Caught expected exception for execute grade 151." << RESET << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << RED << "[FAIL] Caught wrong exception type for execute grade 151: " << e.what() << RESET << std::endl;
    }
}

static void test_form_signing(void)
{
    print_header("Form Signing Logic");

    Form tax_return("Tax Return", 20, 10);
    Bureaucrat ceo("CEO", 1);
    Bureaucrat intern("Intern", 150);
    Bureaucrat manager("Manager", 20);
    Bureaucrat junior("Junior", 21);

    std::cout << "Initial state: " << tax_return << std::endl;

    // Intern tenta assinar (grau 150 > 20) -> Deve falhar (GradeTooLowException)
    intern.signForm(tax_return);
    if (tax_return.isSigned())
    {
        std::cout << RED << "[FAIL] Form was signed by Intern!" << RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << "Passed: Intern failed to sign." << RESET << std::endl;
    }

    // Junior tenta assinar (grau 21 > 20) -> Deve falhar
    junior.signForm(tax_return);
    if (tax_return.isSigned())
    {
        std::cout << RED << "[FAIL] Form was signed by Junior!" << RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << "Passed: Junior failed to sign." << RESET << std::endl;
    }

    // Manager tenta assinar (grau 20 == 20) -> Deve funcionar (Lembre-se: 1 é o maior, 20 >= 20)
    manager.signForm(tax_return);
    if (!tax_return.isSigned())
    {
        std::cout << RED << "[FAIL] Form was not signed by Manager!" << RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << "Passed: Manager signed the form." << RESET << std::endl;
    }

    // CEO tenta assinar um formulário já assinado -> Deve continuar assinado sem erros
    ceo.signForm(tax_return);
    if (!tax_return.isSigned())
    {
        std::cout << RED << "[FAIL] Form lost signature after CEO attempt!" << RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << "Passed: Form remains signed." << RESET << std::endl;
    }
}

static void test_canonical_form(void)
{
    print_header("Form OCF (Copy & Assignment)");

    Form original("Original Form", 42, 21);
    Form copy_target("Target Form", 100, 100);

    // Vamos assinar o original para testar se o estado mutável é copiado
    Bureaucrat signer("Signer", 1);
    signer.signForm(original);

    std::cout << "Original: " << original << std::endl;
    std::cout << "Target Before: " << copy_target << std::endl;

    copy_target = original;

    std::cout << "Target After Assignment: " << copy_target << std::endl;

    // Validação Defensiva Extrema:
    // O nome DEVE permanecer "Target Form" (const), os graus 100 (const),
    // mas o estado isSigned deve ser propagado para true.
    if (copy_target.getName() != "Target Form" ||
        copy_target.getGradeToSign() != 100 ||
        !copy_target.isSigned())
    {
        std::cout << RED << "[FAIL] Assignment operator failed to preserve consts or copy mutable state!" << RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << "Passed: Assignment operator behaves perfectly with const members." << RESET << std::endl;
    }

    Form direct_copy(original);
    std::cout << "Direct Copy Constructor: " << direct_copy << std::endl;
    if (direct_copy.getName() != "Original Form" ||
        direct_copy.getGradeToSign() != 42 ||
        !direct_copy.isSigned())
    {
        std::cout << RED << "[FAIL] Copy constructor failed!" << RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << "Passed: Copy constructor works." << RESET << std::endl;
    }
}

int main(void)
{
    test_form_construction();
    test_form_signing();
    test_canonical_form();

    std::cout << std::endl
              << BOLD << GREEN << "All TDD Tests Completed Successfully." << RESET << std::endl;
    return (0);
}