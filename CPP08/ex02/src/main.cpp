#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <algorithm>
#include <climits>
#include "../include/MutantStack.hpp"
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

template <typename Container1, typename Container2>
static bool compare_iterations(Container1 &c1, Container2 &c2)
{
    typename Container1::iterator it1 = c1.begin();
    typename Container2::iterator it2 = c2.begin();

    while (it1 != c1.end() && it2 != c2.end())
    {
        if (*it1 != *it2)
            return false;
        ++it1;
        ++it2;
    }
    return (it1 == c1.end()) && (it2 == c2.end());
}

template <typename T>
static bool test_const_iteration(const MutantStack<T> &ms, const std::list<T> &lst)
{
    typename MutantStack<T>::const_iterator it_ms = ms.begin();
    typename std::list<T>::const_iterator it_lst = lst.begin();

    while (it_ms != ms.end() && it_lst != lst.end())
    {
        if (*it_ms != *it_lst)
            return false;
        ++it_ms;
        ++it_lst;
    }
    return (it_ms == ms.end()) && (it_lst == lst.end());
}

/* --------------------------------------------------------
 *  Test suites
 * ------------------------------------------------------ */

static void test_subject_example()
{
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);

    bool pass = true;
    pass = pass && (mstack.top() == 17);

    mstack.pop();
    pass = pass && (mstack.size() == 1);

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    // Verificar sequência: 5, 3, 5, 737, 0
    int expected[] = {5, 3, 5, 737, 0};
    int idx = 0;
    while (it != ite)
    {
        if (*it != expected[idx])
        {
            pass = false;
            break;
        }
        ++it;
        ++idx;
    }
    pass = pass && (idx == 5);

    // Teste de conversão para std::stack (exigido pelo subject)
    std::stack<int> s(mstack);
    pass = pass && (s.size() == 5) && (s.top() == 0);

    print_result("subject example: full workflow", pass);
}

static void test_empty_stack()
{
    MutantStack<int> ms;
    print_result("empty stack: begin() == end()", ms.begin() == ms.end());

    int count = 0;
    for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
    {
        ++count;
    }
    print_result("empty stack: iteration count is 0", count == 0);
}

static void test_single_element()
{
    MutantStack<int> ms;
    ms.push(42);

    MutantStack<int>::iterator it = ms.begin();
    print_result("single element: *begin() == 42", *it == 42);
    print_result("single element: ++begin() == end()", ++it == ms.end());
}

static void test_equivalence_with_std_list()
{
    MutantStack<int> ms;
    std::list<int> lst;

    const int NUM_ELEMENTS = 1000;
    for (int i = 0; i < NUM_ELEMENTS; ++i)
    {
        ms.push(i);
        lst.push_back(i);
    }

    print_result("equivalence: MutantStack matches std::list (1000 elements)",
                 compare_iterations(ms, lst));
}

static void test_const_correctness()
{
    MutantStack<int> ms;
    ms.push(10);
    ms.push(20);
    ms.push(30);

    const MutantStack<int> &const_ms = ms;
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);

    print_result("const-correctness: const iteration matches list",
                 test_const_iteration(const_ms, lst));
}

static void test_extreme_values()
{
    MutantStack<int> ms;
    ms.push(INT_MAX);
    ms.push(INT_MIN);
    ms.push(0);
    ms.push(-1);

    std::list<int> lst;
    lst.push_back(INT_MAX);
    lst.push_back(INT_MIN);
    lst.push_back(0);
    lst.push_back(-1);

    print_result("extreme values: iteration matches list",
                 compare_iterations(ms, lst));
}

static void test_large_scale()
{
    const int SIZE = 100000;
    MutantStack<int> ms;
    std::list<int> lst;

    for (int i = 0; i < SIZE; ++i)
    {
        ms.push(i * 2);
        lst.push_back(i * 2);
    }

    print_result("large scale (100k): iteration matches list",
                 compare_iterations(ms, lst));

    // Teste de reverse logic (simulado, já que não temos rbegin/rend por YAGNI)
    // Mas podemos verificar o topo e o início
    print_result("large scale: top() is last element", ms.top() == (SIZE - 1) * 2);

    MutantStack<int>::iterator it = ms.begin();
    print_result("large scale: begin() is first element", *it == 0);
}

static void test_ocf()
{
    bool passed = true;
    try
    {
        MutantStack<int> ms1;
        ms1.push(1);
        ms1.push(2);

        MutantStack<int> ms2(ms1); // Copy constructor
        MutantStack<int> ms3;
        ms3 = ms1; // Assignment operator

        // ms3 = ms3; // REMOVIDO: Evita -Werror,-Wself-assign-overloaded no Clang

        passed = passed && (ms2.size() == 2) && (ms3.size() == 2);

        // Verificar se os valores são os mesmos
        MutantStack<int>::iterator it1 = ms1.begin();
        MutantStack<int>::iterator it2 = ms2.begin();
        MutantStack<int>::iterator it3 = ms3.begin();

        passed = passed && (*it1 == *it2) && (*it2 == *it3);
    }
    catch (...)
    {
        passed = false;
    }
    print_result("Orthodox Canonical Form: copy/assign/destruct safe", passed);
}

static void test_stl_algorithms_compatibility()
{
    MutantStack<int> ms;
    ms.push(5);
    ms.push(2);
    ms.push(8);
    ms.push(1);
    ms.push(9);

    // std::find deve funcionar porque fornecemos iteradores válidos
    MutantStack<int>::iterator it = std::find(ms.begin(), ms.end(), 8);
    print_result("STL algorithm: std::find works", it != ms.end() && *it == 8);

    // std::count
    int count = std::count(ms.begin(), ms.end(), 5);
    print_result("STL algorithm: std::count works", count == 1);
}

/* --------------------------------------------------------
 *  main
 * ------------------------------------------------------ */

int main()
{
    std::cout << BOLD << BRIGHT_CYAN << "=== MutantStack test suite ===" << RESET << std::endl;
    std::cout << std::endl;

    test_subject_example();
    test_empty_stack();
    test_single_element();
    test_equivalence_with_std_list();
    test_const_correctness();
    test_extreme_values();
    test_large_scale();
    test_ocf();
    test_stl_algorithms_compatibility();

    std::cout << std::endl;
    std::cout << BOLD << "=== Results: "
              << GREEN << g_tests_passed << RESET << " passed, "
              << RED << g_tests_failed << RESET << " failed ===" << RESET << std::endl;

    return (g_tests_failed > 0) ? 1 : 0;
}
