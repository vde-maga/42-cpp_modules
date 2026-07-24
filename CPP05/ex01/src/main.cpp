#include "../include/Colors.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/Form.hpp"
#include <iostream>
#include <climits>

int main(void)
{
    bool all_passed = true;

    std::cout << BRIGHT_CYAN
              << "==============================================" << std::endl
              << "    Bureaucrat & Form - Automated Unit Tests" << std::endl
              << "==============================================" << std::endl
              << RESET << std::endl << std::endl;

    /* ----------------------------------------------------------
     * Section 1: Bureaucrat Construction
     * ---------------------------------------------------------- */
    std::cout << BRIGHT_BLUE
              << "--- Section 1: Bureaucrat Construction ---"
              << RESET << std::endl << std::endl;

    /* Test 1: Valid grades */
    {
        std::cout << MAGENTA << "Test 1: Constructor with valid grades (1, 75, 150)" << RESET << std::endl;
        bool passed = true;
        try
        {
            Bureaucrat a("Alice", 1);
            Bureaucrat b("Bob", 75);
            Bureaucrat c("Charlie", 150);

            if (a.getGrade() != 1 || b.getGrade() != 75 || c.getGrade() != 150)
            {
                std::cerr << "  -> FAIL: Grade mismatch" << std::endl;
                passed = false;
                all_passed = false;
            }
            if (a.getName() != "Alice" || b.getName() != "Bob" || c.getName() != "Charlie")
            {
                std::cerr << "  -> FAIL: Name mismatch" << std::endl;
                passed = false;
                all_passed = false;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "  -> FAIL: Unexpected exception: " << e.what() << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 2: Grade too high (0) */
    {
        std::cout << MAGENTA << "Test 2: Constructor with grade 0 (too high)" << RESET << std::endl;
        bool passed = false;
        try
        {
            Bureaucrat b("High", 0);
            std::cerr << "  -> FAIL: Expected GradeTooHighException" << std::endl;
            all_passed = false;
        }
        catch (const Bureaucrat::GradeTooHighException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 3: Grade too low (151) */
    {
        std::cout << MAGENTA << "Test 3: Constructor with grade 151 (too low)" << RESET << std::endl;
        bool passed = false;
        try
        {
            Bureaucrat b("Low", 151);
            std::cerr << "  -> FAIL: Expected GradeTooLowException" << std::endl;
            all_passed = false;
        }
        catch (const Bureaucrat::GradeTooLowException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 4: Negative grade */
    {
        std::cout << MAGENTA << "Test 4: Constructor with negative grade (-5)" << RESET << std::endl;
        bool passed = false;
        try
        {
            Bureaucrat b("Neg", -5);
            std::cerr << "  -> FAIL: Expected GradeTooHighException" << std::endl;
            all_passed = false;
        }
        catch (const Bureaucrat::GradeTooHighException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 5: INT_MAX grade */
    {
        std::cout << MAGENTA << "Test 5: Constructor with INT_MAX grade" << RESET << std::endl;
        bool passed = false;
        try
        {
            Bureaucrat b("Max", INT_MAX);
            std::cerr << "  -> FAIL: Expected GradeTooLowException" << std::endl;
            all_passed = false;
        }
        catch (const Bureaucrat::GradeTooLowException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 6: INT_MIN grade */
    {
        std::cout << MAGENTA << "Test 6: Constructor with INT_MIN grade" << RESET << std::endl;
        bool passed = false;
        try
        {
            Bureaucrat b("Min", INT_MIN);
            std::cerr << "  -> FAIL: Expected GradeTooHighException" << std::endl;
            all_passed = false;
        }
        catch (const Bureaucrat::GradeTooHighException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* ----------------------------------------------------------
     * Section 2: Bureaucrat Grade Modification
     * ---------------------------------------------------------- */
    std::cout << BRIGHT_BLUE
              << "--- Section 2: Bureaucrat Grade Modification ---"
              << RESET << std::endl << std::endl;

    /* Test 7: Normal increment/decrement */
    {
        std::cout << MAGENTA << "Test 7: Normal increment and decrement" << RESET << std::endl;
        bool passed = true;
        try
        {
            Bureaucrat b("Mid", 75);
            b.incrementGrade();
            if (b.getGrade() != 74)
            {
                std::cerr << "  -> FAIL: Expected grade 74, got " << b.getGrade() << std::endl;
                passed = false;
                all_passed = false;
            }
            b.decrementGrade();
            if (b.getGrade() != 75)
            {
                std::cerr << "  -> FAIL: Expected grade 75, got " << b.getGrade() << std::endl;
                passed = false;
                all_passed = false;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "  -> FAIL: Unexpected exception: " << e.what() << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 8: Increment at grade 1 (boundary) */
    {
        std::cout << MAGENTA << "Test 8: incrementGrade at grade 1 (should throw)" << RESET << std::endl;
        bool passed = false;
        try
        {
            Bureaucrat b("Top", 1);
            b.incrementGrade();
            std::cerr << "  -> FAIL: Expected GradeTooHighException" << std::endl;
            all_passed = false;
        }
        catch (const Bureaucrat::GradeTooHighException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 9: Decrement at grade 150 (boundary) */
    {
        std::cout << MAGENTA << "Test 9: decrementGrade at grade 150 (should throw)" << RESET << std::endl;
        bool passed = false;
        try
        {
            Bureaucrat b("Bottom", 150);
            b.decrementGrade();
            std::cerr << "  -> FAIL: Expected GradeTooLowException" << std::endl;
            all_passed = false;
        }
        catch (const Bureaucrat::GradeTooLowException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 10: Grade unchanged after failed increment */
    {
        std::cout << MAGENTA << "Test 10: Grade remains unchanged after failed increment" << RESET << std::endl;
        bool passed = true;
        try
        {
            Bureaucrat b("Top", 1);
            try
            {
                b.incrementGrade();
            }
            catch (const std::exception &)
            {
            }
            if (b.getGrade() != 1)
            {
                std::cerr << "  -> FAIL: Grade was modified, expected 1, got " << b.getGrade() << std::endl;
                passed = false;
                all_passed = false;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "  -> FAIL: Unexpected exception: " << e.what() << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* ----------------------------------------------------------
     * Section 3: Bureaucrat Copy Semantics
     * ---------------------------------------------------------- */
    std::cout << BRIGHT_BLUE
              << "--- Section 3: Bureaucrat Copy Semantics ---"
              << RESET << std::endl << std::endl;

    /* Test 11: Copy constructor */
    {
        std::cout << MAGENTA << "Test 11: Bureaucrat copy constructor" << RESET << std::endl;
        bool passed = true;
        Bureaucrat original("Original", 42);
        Bureaucrat copy(original);

        if (copy.getName() != original.getName() || copy.getGrade() != original.getGrade())
        {
            std::cerr << "  -> FAIL: Copy does not match original" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 12: Assignment operator */
    {
        std::cout << MAGENTA << "Test 12: Bureaucrat assignment operator" << RESET << std::endl;
        bool passed = true;
        Bureaucrat a("Alpha", 10);
        Bureaucrat b("Beta", 100);
        b = a;

        if (b.getName() != "Alpha" || b.getGrade() != 10)
        {
            std::cerr << "  -> FAIL: Assignment failed" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 13: Self-assignment */
    {
        std::cout << MAGENTA << "Test 13: Bureaucrat self-assignment" << RESET << std::endl;
        bool passed = true;
        Bureaucrat a("Self", 50);
        a = a;

        if (a.getName() != "Self" || a.getGrade() != 50)
        {
            std::cerr << "  -> FAIL: Self-assignment corrupted object" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* ----------------------------------------------------------
     * Section 4: Form Construction
     * ---------------------------------------------------------- */
    std::cout << BRIGHT_BLUE
              << "--- Section 4: Form Construction ---"
              << RESET << std::endl << std::endl;

    /* Test 14: Valid Form construction */
    {
        std::cout << MAGENTA << "Test 14: Form constructor with valid grades" << RESET << std::endl;
        bool passed = true;
        try
        {
            Form f("TaxForm", 50, 25);
            if (f.getName() != "TaxForm" || f.isSigned() != false || f.getGradeToSign() != 50 || f.getGradeToExecute() != 25)
            {
                std::cerr << "  -> FAIL: Attributes mismatch" << std::endl;
                passed = false;
                all_passed = false;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "  -> FAIL: Unexpected exception: " << e.what() << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 15: Form sign grade too high */
    {
        std::cout << MAGENTA << "Test 15: Form with sign grade 0 (too high)" << RESET << std::endl;
        bool passed = false;
        try
        {
            Form f("Bad", 0, 50);
            std::cerr << "  -> FAIL: Expected GradeTooHighException" << std::endl;
            all_passed = false;
        }
        catch (const Form::GradeTooHighException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 16: Form sign grade too low */
    {
        std::cout << MAGENTA << "Test 16: Form with sign grade 151 (too low)" << RESET << std::endl;
        bool passed = false;
        try
        {
            Form f("Bad", 151, 50);
            std::cerr << "  -> FAIL: Expected GradeTooLowException" << std::endl;
            all_passed = false;
        }
        catch (const Form::GradeTooLowException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 17: Form execute grade too high */
    {
        std::cout << MAGENTA << "Test 17: Form with execute grade 0 (too high)" << RESET << std::endl;
        bool passed = false;
        try
        {
            Form f("Bad", 50, 0);
            std::cerr << "  -> FAIL: Expected GradeTooHighException" << std::endl;
            all_passed = false;
        }
        catch (const Form::GradeTooHighException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 18: Form execute grade too low */
    {
        std::cout << MAGENTA << "Test 18: Form with execute grade 151 (too low)" << RESET << std::endl;
        bool passed = false;
        try
        {
            Form f("Bad", 50, 151);
            std::cerr << "  -> FAIL: Expected GradeTooLowException" << std::endl;
            all_passed = false;
        }
        catch (const Form::GradeTooLowException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 19: Form with INT_MAX grades */
    {
        std::cout << MAGENTA << "Test 19: Form with INT_MAX sign grade" << RESET << std::endl;
        bool passed = false;
        try
        {
            Form f("Extreme", INT_MAX, 50);
            std::cerr << "  -> FAIL: Expected GradeTooLowException" << std::endl;
            all_passed = false;
        }
        catch (const Form::GradeTooLowException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* ----------------------------------------------------------
     * Section 5: Form beSigned
     * ---------------------------------------------------------- */
    std::cout << BRIGHT_BLUE
              << "--- Section 5: Form beSigned ---"
              << RESET << std::endl << std::endl;

    /* Test 20: beSigned with exact required grade */
    {
        std::cout << MAGENTA << "Test 20: beSigned with exact required grade (50==50)" << RESET << std::endl;
        bool passed = true;
        Form f("Permit", 50, 30);
        Bureaucrat b("Signer", 50);
        try
        {
            f.beSigned(b);
            if (!f.isSigned())
            {
                std::cerr << "  -> FAIL: Form should be signed" << std::endl;
                passed = false;
                all_passed = false;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "  -> FAIL: Unexpected exception: " << e.what() << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 21: beSigned with better grade (lower number) */
    {
        std::cout << MAGENTA << "Test 21: beSigned with better grade (1 < 50)" << RESET << std::endl;
        bool passed = true;
        Form f("Permit", 50, 30);
        Bureaucrat b("Boss", 1);
        try
        {
            f.beSigned(b);
            if (!f.isSigned())
            {
                std::cerr << "  -> FAIL: Form should be signed" << std::endl;
                passed = false;
                all_passed = false;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "  -> FAIL: Unexpected exception: " << e.what() << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 22: beSigned with worse grade (higher number) */
    {
        std::cout << MAGENTA << "Test 22: beSigned with worse grade (51 > 50)" << RESET << std::endl;
        bool passed = false;
        Form f("Permit", 50, 30);
        Bureaucrat b("Intern", 51);
        try
        {
            f.beSigned(b);
            std::cerr << "  -> FAIL: Expected GradeTooLowException" << std::endl;
            all_passed = false;
        }
        catch (const Form::GradeTooLowException &)
        {
            if (f.isSigned())
            {
                std::cerr << "  -> FAIL: Form should NOT be signed" << std::endl;
                all_passed = false;
            }
            else
            {
                passed = true;
            }
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 23: beSigned idempotent (already signed) */
    {
        std::cout << MAGENTA << "Test 23: beSigned on already-signed form (idempotent)" << RESET << std::endl;
        bool passed = true;
        Form f("Permit", 50, 30);
        Bureaucrat b("Signer", 50);
        try
        {
            f.beSigned(b);
            f.beSigned(b);
            if (!f.isSigned())
            {
                std::cerr << "  -> FAIL: Form should remain signed" << std::endl;
                passed = false;
                all_passed = false;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "  -> FAIL: Unexpected exception on second sign: " << e.what() << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 24: beSigned at boundary (grade 1 signing grade 1 form) */
    {
        std::cout << MAGENTA << "Test 24: beSigned at exact boundary (grade 1, form 1)" << RESET << std::endl;
        bool passed = true;
        Form f("TopForm", 1, 1);
        Bureaucrat b("CEO", 1);
        try
        {
            f.beSigned(b);
            if (!f.isSigned())
            {
                std::cerr << "  -> FAIL: Form should be signed" << std::endl;
                passed = false;
                all_passed = false;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "  -> FAIL: Unexpected exception: " << e.what() << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 25: beSigned fails at boundary (grade 2 signing grade 1 form) */
    {
        std::cout << MAGENTA << "Test 25: beSigned fails (grade 2 > form grade 1)" << RESET << std::endl;
        bool passed = false;
        Form f("TopForm", 1, 1);
        Bureaucrat b("VP", 2);
        try
        {
            f.beSigned(b);
            std::cerr << "  -> FAIL: Expected GradeTooLowException" << std::endl;
            all_passed = false;
        }
        catch (const Form::GradeTooLowException &)
        {
            passed = true;
        }
        catch (...)
        {
            std::cerr << "  -> FAIL: Wrong exception type" << std::endl;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* ----------------------------------------------------------
     * Section 6: Bureaucrat::signForm Integration
     * ---------------------------------------------------------- */
    std::cout << BRIGHT_BLUE
              << "--- Section 6: Bureaucrat::signForm Integration ---"
              << RESET << std::endl << std::endl;

    /* Test 26: signForm success */
    {
        std::cout << MAGENTA << "Test 26: signForm success (grade 30 signs form 50)" << RESET << std::endl;
        bool passed = true;
        Form f("Contract", 50, 25);
        Bureaucrat b("Manager", 30);
        std::cout << "  ";
        b.signForm(f);
        if (!f.isSigned())
        {
            std::cerr << "  -> FAIL: Form should be signed" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 27: signForm failure */
    {
        std::cout << MAGENTA << "Test 27: signForm failure (grade 100 cannot sign form 50)" << RESET << std::endl;
        bool passed = true;
        Form f("Contract", 50, 25);
        Bureaucrat b("Intern", 100);
        std::cout << "  ";
        b.signForm(f);
        if (f.isSigned())
        {
            std::cerr << "  -> FAIL: Form should NOT be signed" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 28: Multiple bureaucrats signing same form */
    {
        std::cout << MAGENTA << "Test 28: Multiple bureaucrats attempt same form" << RESET << std::endl;
        bool passed = true;
        Form f("Shared", 50, 50);
        Bureaucrat low("Low", 100);
        Bureaucrat high("High", 1);
        std::cout << "  ";
        low.signForm(f);
        if (f.isSigned())
        {
            std::cerr << "  -> FAIL: Form should not be signed by low grade" << std::endl;
            passed = false;
            all_passed = false;
        }
        std::cout << "  ";
        high.signForm(f);
        if (!f.isSigned())
        {
            std::cerr << "  -> FAIL: Form should be signed by high grade" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* ----------------------------------------------------------
     * Section 7: Form Copy Semantics
     * ---------------------------------------------------------- */
    std::cout << BRIGHT_BLUE
              << "--- Section 7: Form Copy Semantics ---"
              << RESET << std::endl << std::endl;

    /* Test 29: Copy constructor (unsigned form) */
    {
        std::cout << MAGENTA << "Test 29: Form copy constructor (unsigned)" << RESET << std::endl;
        bool passed = true;
        Form original("Original", 50, 30);
        Form copy(original);
        if (copy.getName() != original.getName() || copy.isSigned() != original.isSigned() || copy.getGradeToSign() != original.getGradeToSign() || copy.getGradeToExecute() != original.getGradeToExecute())
        {
            std::cerr << "  -> FAIL: Copy does not match original" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 30: Copy constructor (signed form) */
    {
        std::cout << MAGENTA << "Test 30: Form copy constructor (signed)" << RESET << std::endl;
        bool passed = true;
        Form original("Signed", 50, 30);
        Bureaucrat b("Signer", 10);
        original.beSigned(b);
        Form copy(original);
        if (!copy.isSigned())
        {
            std::cerr << "  -> FAIL: Copy of signed form should be signed" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 31: Assignment operator */
    {
        std::cout << MAGENTA << "Test 31: Form assignment operator" << RESET << std::endl;
        bool passed = true;
        Form a("Alpha", 10, 20);
        Form b("Beta", 100, 120);
        b = a;
        if (b.getName() != "Alpha" || b.getGradeToSign() != 10 || b.getGradeToExecute() != 20)
        {
            std::cerr << "  -> FAIL: Assignment failed" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 32: Self-assignment */
    {
        std::cout << MAGENTA << "Test 32: Form self-assignment" << RESET << std::endl;
        bool passed = true;
        Form f("Self", 50, 30);
        f = f;
        if (f.getName() != "Self" || f.getGradeToSign() != 50 || f.getGradeToExecute() != 30)
        {
            std::cerr << "  -> FAIL: Self-assignment corrupted object" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 33: Copy independence */
    {
        std::cout << MAGENTA << "Test 33: Copy independence - signing copy does not affect original" << RESET << std::endl;
        bool passed = true;
        Form original("Original", 50, 30);
        Form copy(original);
        Bureaucrat b("Signer", 10);
        copy.beSigned(b);
        if (original.isSigned())
        {
            std::cerr << "  -> FAIL: Original should NOT be signed" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (!copy.isSigned())
        {
            std::cerr << "  -> FAIL: Copy should be signed" << std::endl;
            passed = false;
            all_passed = false;
        }
        if (passed)
            std::cout << "  -> " << BRIGHT_GREEN << "PASS" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* ----------------------------------------------------------
     * Section 8: Output Operators
     * ---------------------------------------------------------- */
    std::cout << BRIGHT_BLUE
              << "--- Section 8: Output Operators ---"
              << RESET << std::endl << std::endl;

    /* Test 34: Bureaucrat operator<< */
    {
        std::cout << MAGENTA << "Test 34: Bureaucrat operator<< output" << RESET << std::endl;
        Bureaucrat b("Display", 42);
        std::cout << "  " << b << std::endl;
        std::cout << "  -> " << BRIGHT_GREEN << "PASS (manual check)" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 35: Form operator<< (unsigned) */
    {
        std::cout << MAGENTA << "Test 35: Form operator<< output (unsigned)" << RESET << std::endl;
        Form f("DisplayForm", 50, 25);
        std::cout << "  " << f << std::endl;
        std::cout << "  -> " << BRIGHT_GREEN << "PASS (manual check)" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* Test 36: Form operator<< (signed) */
    {
        std::cout << MAGENTA << "Test 36: Form operator<< output (signed)" << RESET << std::endl;
        Form f("SignedForm", 50, 25);
        Bureaucrat b("Signer", 10);
        f.beSigned(b);
        std::cout << "  " << f << std::endl;
        std::cout << "  -> " << BRIGHT_GREEN << "PASS (manual check)" << RESET << std::endl;
        std::cout << std::endl;
    }

    /* ----------------------------------------------------------
     * Summary
     * ---------------------------------------------------------- */
    std::cout << BRIGHT_CYAN
              << "==============================================" << std::endl;
    if (all_passed)
        std::cout << BRIGHT_GREEN << "    ALL TESTS PASSED!" << RESET << std::endl;
    else
        std::cout << BRIGHT_RED << "    SOME TESTS FAILED!" << RESET << std::endl;
    std::cout << BRIGHT_CYAN
              << "==============================================" << RESET << std::endl;

    return (all_passed ? 0 : 1);
}