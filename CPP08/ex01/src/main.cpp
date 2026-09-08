#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include "../include/Span.hpp"
#include "../include/Colors.hpp"

static int g_tests_passed = 0;
static int g_tests_failed = 0;

static void print_result(const char *test_name, bool passed)
{
    if (passed)
    {
        std::cout << GREEN << BOLD << "[PASS]" << RESET << " " << test_name << std::endl;
        ++g_tests_passed;
    }
    else
    {
        std::cout << RED << BOLD << "[FAIL]" << RESET << " " << test_name << std::endl;
        ++g_tests_failed;
    }
}

/* --------------------------------------------------------
 *  Helpers
 * ------------------------------------------------------ */

static bool test_throws_too_little(Span &sp)
{
    try
    {
        sp.shortestSpan();
        return false;
    }
    catch (const Span::TooLittleElementsException &)
    {
        return true;
    }
    catch (...)
    {
        return false;
    }
}

static bool test_throws_too_many(Span &sp, int val)
{
    try
    {
        sp.addNumber(val);
        return false;
    }
    catch (const Span::TooManyElementsException &)
    {
        return true;
    }
    catch (...)
    {
        return false;
    }
}

template <typename It>
static bool test_add_numbers_throws(Span &sp, It first, It last)
{
    try
    {
        sp.addNumbers(first, last);
        return false;
    }
    catch (const Span::TooManyElementsException &)
    {
        return true;
    }
    catch (...)
    {
        return false;
    }
}

/* --------------------------------------------------------
 *  Test suites
 * ------------------------------------------------------ */

static void test_subject_example()
{
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    print_result("subject example: shortestSpan == 2", sp.shortestSpan() == 2);
    print_result("subject example: longestSpan == 14", sp.longestSpan() == 14);
}

static void test_empty_and_single_element()
{
    Span sp0(0);
    print_result("empty span: shortestSpan throws", test_throws_too_little(sp0));
    print_result("empty span: longestSpan throws", test_throws_too_little(sp0));

    Span sp1(1);
    sp1.addNumber(42);
    print_result("single element span: shortestSpan throws", test_throws_too_little(sp1));
    print_result("single element span: longestSpan throws", test_throws_too_little(sp1));
}

static void test_capacity_limits()
{
    Span sp(2);
    sp.addNumber(10);
    sp.addNumber(20);
    print_result("at max capacity: addNumber throws", test_throws_too_many(sp, 30));
}

static void test_extreme_values_overflow_protection()
{
    Span sp(2);
    sp.addNumber(INT_MIN);
    sp.addNumber(INT_MAX);

    // INT_MAX - INT_MIN em unsigned int é 4294967295.
    // Se houvesse UB signed, o comportamento seria imprevisível.
    print_result("extreme values: longestSpan handles INT_MIN/INT_MAX without UB",
                 sp.longestSpan() == 4294967295U);

    print_result("extreme values: shortestSpan handles INT_MIN/INT_MAX without UB",
                 sp.shortestSpan() == 4294967295U);
}

static void test_negative_numbers()
{
    Span sp(3);
    sp.addNumber(-100);
    sp.addNumber(-50);
    sp.addNumber(-10);

    print_result("negative numbers: shortestSpan == 40", sp.shortestSpan() == 40);
    print_result("negative numbers: longestSpan == 90", sp.longestSpan() == 90);
}

static void test_add_numbers_vector()
{
    Span sp(5);
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    sp.addNumbers(v.begin(), v.end());
    print_result("addNumbers from vector: fills correctly", sp.longestSpan() == 4);
}

static void test_add_numbers_list()
{
    Span sp(3);
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);

    sp.addNumbers(lst.begin(), lst.end());
    print_result("addNumbers from list: fills correctly", sp.shortestSpan() == 10);
}

static void test_add_numbers_array()
{
    Span sp(3);
    int arr[] = {5, 15, 25};
    sp.addNumbers(arr, arr + 3);
    print_result("addNumbers from raw array: fills correctly", sp.longestSpan() == 20);
}

static void test_add_numbers_defensive_throws()
{
    Span sp(2);
    sp.addNumber(1); // 1 slot left
    std::vector<int> v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(4); // 3 elements

    // Deve lançar ANTES de adicionar qualquer coisa, preservando o estado
    print_result("addNumbers defensive: throws before partial modification",
                 test_add_numbers_throws(sp, v.begin(), v.end()));

    // Verifica se o estado anterior foi preservado (apenas 1 elemento)
    try
    {
        sp.shortestSpan();
        print_result("addNumbers defensive: state preserved (no partial fill)", false);
    }
    catch (const Span::TooLittleElementsException &)
    {
        print_result("addNumbers defensive: state preserved (no partial fill)", true);
    }
    catch (...)
    {
        print_result("addNumbers defensive: state preserved (no partial fill)", false);
    }
}

static void test_large_scale()
{
    const unsigned int SIZE = 100000;
    Span sp(SIZE);
    std::vector<int> v;
    v.reserve(SIZE);
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        v.push_back(i * 2);
    }

    sp.addNumbers(v.begin(), v.end());
    print_result("large scale (100k): shortestSpan == 2", sp.shortestSpan() == 2);
    print_result("large scale (100k): longestSpan == 199998", sp.longestSpan() == 199998);
}

static void test_exception_ocf()
{
    bool passed = true;
    try
    {
        Span::TooManyElementsException e1;
        Span::TooManyElementsException e2(e1);
        Span::TooManyElementsException e3;
        e3 = e2;
        (void)e3.what();
    }
    catch (...)
    {
        passed = false;
    }
    print_result("TooManyElementsException OCF is safe", passed);
}

/* --------------------------------------------------------
 *  main
 * ------------------------------------------------------ */

int main()
{
    std::cout << BOLD << BRIGHT_CYAN << "=== Span test suite ===" << RESET << std::endl;
    std::cout << std::endl;

    test_subject_example();
    test_empty_and_single_element();
    test_capacity_limits();
    test_extreme_values_overflow_protection();
    test_negative_numbers();
    test_add_numbers_vector();
    test_add_numbers_list();
    test_add_numbers_array();
    test_add_numbers_defensive_throws();
    test_large_scale();
    test_exception_ocf();

    std::cout << std::endl;
    std::cout << BOLD << "=== Results: "
              << GREEN << g_tests_passed << RESET << " passed, "
              << RED << g_tests_failed << RESET << " failed ===" << RESET << std::endl;

    return (g_tests_failed > 0) ? 1 : 0;
}
