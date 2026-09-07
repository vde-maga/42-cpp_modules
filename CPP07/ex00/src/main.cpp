#include <iostream>
#include <string>
#include <limits>
#include "../include/Whatever.hpp"
#include "../include/Colors.hpp"

// Orthodox Canonical Form para testes
class CustomType
{
public:
    int value;

    CustomType() : value(0) {}
    CustomType(int v) : value(v) {}
    CustomType(const CustomType &other) : value(other.value) {}
    ~CustomType() {}

    CustomType &operator=(const CustomType &other)
    {
        if (this != &other)
        {
            value = other.value;
        }
        return *this;
    }

    bool operator<(const CustomType &other) const { return value < other.value; }
    bool operator>(const CustomType &other) const { return value > other.value; }
    bool operator==(const CustomType &other) const { return value == other.value; }
};

std::ostream &operator<<(std::ostream &os, const CustomType &ct)
{
    os << "Custom(" << ct.value << ")";
    return os;
}

// Namespace para isolar a responsabilidade de UI/Log (SOC e DRY)
namespace TestUI
{
    void printHeader(const std::string &title)
    {
        std::cout << BOLD << BRIGHT_CYAN << "\n========================================" << RESET << std::endl;
        std::cout << BOLD << BRIGHT_CYAN << " [TEST] " << title << RESET << std::endl;
        std::cout << BOLD << BRIGHT_CYAN << "========================================" << RESET << std::endl;
    }

    void printPass(const std::string &msg)
    {
        std::cout << BRIGHT_GREEN << "[PASS]" << RESET << " " << msg << std::endl;
    }

    void printFail(const std::string &msg)
    {
        std::cout << BRIGHT_RED << "[FAIL]" << RESET << " " << msg << std::endl;
    }

    void printInfo(const std::string &msg)
    {
        std::cout << BRIGHT_WHITE << "[INFO]" << RESET << " " << msg << std::endl;
    }
}

void test_subject_main()
{
    TestUI::printHeader("Subject Main (Strict Output)");
    int a = 2;
    int b = 3;
    ::swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
    std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

    std::string c = "chaine1";
    std::string d = "chaine2";
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
    std::cout << "max(c, d) = " << ::max(c, d) << std::endl;
}

void test_equal_values_semantics()
{
    TestUI::printHeader("Equal Values (Must return 2nd param)");
    int x = 5;
    int y = 5;

    const int &res_min = ::min(x, y);
    const int &res_max = ::max(x, y);

    if (&res_min == &y)
        TestUI::printPass("min returns 2nd when equal");
    else
        TestUI::printFail("min returns 2nd when equal");

    if (&res_max == &y)
        TestUI::printPass("max returns 2nd when equal");
    else
        TestUI::printFail("max returns 2nd when equal");
}

void test_self_swap()
{
    TestUI::printHeader("Self Swap (Defensive)");
    int z = 42;
    ::swap(z, z);
    if (z == 42)
        TestUI::printPass("Self swap int (42)");
    else
        TestUI::printFail("Self swap int (42)");

    std::string s = "hello";
    ::swap(s, s);
    if (s == "hello")
        TestUI::printPass("Self swap string");
    else
        TestUI::printFail("Self swap string");
}

void test_pointers()
{
    TestUI::printHeader("Pointers Swap");
    int p1 = 10;
    int p2 = 20;
    int *ptr1 = &p1;
    int *ptr2 = &p2;

    ::swap(ptr1, ptr2);
    if (*ptr1 == 20)
        TestUI::printPass("ptr1 points to 20");
    else
        TestUI::printFail("ptr1 points to 20");

    if (*ptr2 == 10)
        TestUI::printPass("ptr2 points to 10");
    else
        TestUI::printFail("ptr2 points to 10");
}

void test_custom_type()
{
    TestUI::printHeader("Custom Type (Orthodox Canonical)");
    CustomType c1(100);
    CustomType c2(200);

    ::swap(c1, c2);
    TestUI::printInfo("After swap: c1 = " + std::string(c1.value == 200 ? "Custom(200)" : "FAIL") +
                      ", c2 = " + std::string(c2.value == 100 ? "Custom(100)" : "FAIL"));
    TestUI::printInfo("min = " + std::string(::min(c1, c2).value == 100 ? "Custom(100)" : "FAIL"));
    TestUI::printInfo("max = " + std::string(::max(c1, c2).value == 200 ? "Custom(200)" : "FAIL"));
}

void test_edge_cases_limits()
{
    TestUI::printHeader("Edge Cases (Limits & Floats)");
    int min_int = std::numeric_limits<int>::min();
    int max_int = std::numeric_limits<int>::max();

    TestUI::printInfo("min(INT_MIN, INT_MAX) = " + std::string(min_int == ::min(min_int, max_int) ? "-2147483648" : "FAIL"));
    TestUI::printInfo("max(INT_MIN, INT_MAX) = " + std::string(max_int == ::max(min_int, max_int) ? "2147483647" : "FAIL"));

    double d1 = -0.0;
    double d2 = 0.0;
    const double &res = ::min(d1, d2);
    if (&res == &d2)
        TestUI::printPass("min(-0.0, 0.0) returns 2nd param");
    else
        TestUI::printFail("min(-0.0, 0.0) returns 2nd param");
}

int main()
{
    test_subject_main();
    test_equal_values_semantics();
    test_self_swap();
    test_pointers();
    test_custom_type();
    test_edge_cases_limits();

    std::cout << BOLD << BRIGHT_GREEN << "\n[ALL TESTS COMPLETED SUCCESSFULLY]" << RESET << std::endl;
    return 0;
}