#include "Bureaucrat.hpp"
#include "Colors.hpp"
#include <iostream>
#include <sstream>
#include <climits>

// --------------------- Test Framework Macros & Helpers ---------------------

static int g_tests_passed = 0;
static int g_tests_total = 0;

static void assertTest(bool condition, const std::string& test_name) {
    ++g_tests_total;
    if (condition) {
        ++g_tests_passed;
        std::cout << BRIGHT_GREEN << "[PASS] " << RESET << test_name << std::endl;
    } else {
        std::cout << BRIGHT_RED << "[FAIL] " << RESET << test_name << std::endl;
    }
}

static void printSection(const std::string& title) {
    std::cout << std::endl << BOLD BG_MAGENTA << " " << title << " " << RESET << std::endl;
}

// ----------------------------- Helper Functions ----------------------------

static std::string captureBureaucratOutput(const Bureaucrat& b) {
    std::ostringstream oss;
    oss << b;
    return oss.str();
}

// ----------------------------- Destructive Tests ----------------------------

void testOrthodoxCanonicalForm() {
    printSection("1. Orthodox Canonical Form & Const-Correctness");
    
    Bureaucrat b1;
    assertTest(b1.getName() == "Default" && b1.getGrade() == 150, "Default constructor initializes correctly");

    Bureaucrat b2("Alice", 50);
    Bureaucrat b3(b2);
    assertTest(b3.getName() == "Alice" && b3.getGrade() == 50, "Copy constructor deep copies correctly");

    Bureaucrat b4("Bob", 10);
    b4 = b2;
    assertTest(b4.getName() == "Alice" && b4.getGrade() == 50, "Assignment operator deep copies correctly");

    /* Test const-correctness and operator<< */
    const Bureaucrat c("Const", 1);
    std::string expected = "Const, bureaucrat grade 1";
    assertTest(captureBureaucratOutput(c) == expected, "operator<< formatted correctly on const object");
}

void testValidGradeBoundaries() {
    printSection("2. Valid Grade Boundaries");

    Bureaucrat high("Highest", 1);
    Bureaucrat low("Lowest", 150);

    assertTest(high.getGrade() == 1, "Grade 1 is valid (Highest possible)");
    assertTest(low.getGrade() == 150, "Grade 150 is valid (Lowest possible)");
}

void testConstructionExceptions() {
    printSection("3. Construction Exceptions (Too High & Too Low)");

    bool caught_high = false;
    try {
        Bureaucrat b("Zero", 0);
    } catch (const Bureaucrat::GradeTooHighException& e) {
        caught_high = true;
    } catch (...) {}

    assertTest(caught_high, "Constructing with grade 0 throws GradeTooHighException");

    bool caught_low = false;
    try {
        Bureaucrat b("Huge", 151);
    } catch (const Bureaucrat::GradeTooLowException& e) {
        caught_low = true;
    } catch (...) {}

    assertTest(caught_low, "Constructing with grade 151 throws GradeTooLowException");
}

void testIncrementDecrementLogic() {
    printSection("4. Increment & Decrement Logic & Exceptions");

    Bureaucrat b("Mover", 75);
    b.incrementGrade();
    assertTest(b.getGrade() == 74, "incrementGrade reduces grade from 75 to 74");

    b.decrementGrade();
    b.decrementGrade();
    assertTest(b.getGrade() == 76, "decrementGrade increases grade from 74 to 76");

    /* Test Exceptions on boundaries */
    Bureaucrat top("Top", 1);
    bool caught_top_inc = false;
    try {
        top.incrementGrade();
    } catch (const Bureaucrat::GradeTooHighException& e) {
        caught_top_inc = true;
    }
    assertTest(caught_top_inc && top.getGrade() == 1, "Incrementing grade 1 throws GradeTooHighException and grade remains 1");

    Bureaucrat bottom("Bottom", 150);
    bool caught_bottom_dec = false;
    try {
        bottom.decrementGrade();
    } catch (const Bureaucrat::GradeTooLowException& e) {
        caught_bottom_dec = true;
    }
    assertTest(caught_bottom_dec && bottom.getGrade() == 150, "Decrementing grade 150 throws GradeTooLowException and grade remains 150");
}

void testExtremeOverflowDefense() {
    printSection("5. Extreme Overflow/Underflow Defense (Zero UB)");

    bool caught_high = false;
    try {
        Bureaucrat b("IntMin", INT_MIN);
    } catch (const Bureaucrat::GradeTooHighException& e) {
        caught_high = true;
    }
    assertTest(caught_high, "Constructing with INT_MIN throws GradeTooHighException safely (no underflow)");

    bool caught_low = false;
    try {
        Bureaucrat b("IntMax", INT_MAX);
    } catch (const Bureaucrat::GradeTooLowException& e) {
        caught_low = true;
    }
    assertTest(caught_low, "Constructing with INT_MAX throws GradeTooLowException safely (no overflow)");
}

void testExceptionInheritanceCatch() {
    printSection("6. Polymorphic Exception Catching (Subject Requirement)");

    bool caught_base = false;
    try {
        Bureaucrat b("Fail", -5);
    } catch (std::exception& e) { /* Deve ser apanhável por std::exception& */
        caught_base = true;
    }
    assertTest(caught_base, "Bureaucrat exception is catchable by std::exception&");
}

int main() {
    std::cout << BOLD YELLOW << "STARTING BUREAUCRAT DESTRUCTIVE TEST SUITE" << RESET << std::endl;

    testOrthodoxCanonicalForm();
    testValidGradeBoundaries();
    testConstructionExceptions();
    testIncrementDecrementLogic();
    testExtremeOverflowDefense();
    testExceptionInheritanceCatch();

    std::cout << std::endl << BOLD << "=====================================" << RESET << std::endl;
    std::cout << BOLD << "TOTAL: " << g_tests_passed << "/" << g_tests_total << " tests passed." << RESET << std::endl;

    if (g_tests_passed == g_tests_total)
        std::cout << BRIGHT_GREEN << "ALL TESTS PASSED!" << RESET << std::endl;
    else
        std::cout << BRIGHT_RED << "SOME TESTS FAILED!" << RESET << std::endl;

    return (g_tests_passed != g_tests_total);
}
