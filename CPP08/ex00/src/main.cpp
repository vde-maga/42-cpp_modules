#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <climits>
#include <cstdlib>
#include "../include/Easyfind.hpp"
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

template <typename Container>
static bool test_find_exists(Container &c, int target, int expected_index)
{
    try
    {
        typename Container::iterator it = easyfind(c, target);
        typename Container::iterator begin = c.begin();
        int index = 0;
        for (typename Container::iterator jt = begin; jt != it; ++jt)
            ++index;
        return index == expected_index;
    }
    catch (...)
    {
        return false;
    }
}

template <typename Container>
static bool test_find_not_exists(const Container &c, int target)
{
    try
    {
        easyfind(c, target);
        return false;
    }
    catch (const NotFoundException &)
    {
        return true;
    }
    catch (...)
    {
        return false;
    }
}

template <typename Container>
static bool test_find_const(const Container &c, int target, int expected_index)
{
    try
    {
        typename Container::const_iterator it = easyfind(c, target);
        typename Container::const_iterator begin = c.begin();
        int index = 0;
        for (typename Container::const_iterator jt = begin; jt != it; ++jt)
            ++index;
        return index == expected_index;
    }
    catch (...)
    {
        return false;
    }
}

/* --------------------------------------------------------
 *  Test suites
 * ------------------------------------------------------ */

static void test_vector_basic()
{
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    print_result("vector: find first element", test_find_exists(v, 10, 0));
    print_result("vector: find middle element", test_find_exists(v, 30, 2));
    print_result("vector: find last element", test_find_exists(v, 50, 4));
    print_result("vector: element not found throws", test_find_not_exists(v, 99));
}

static void test_empty_containers()
{
    std::vector<int> vv;
    std::list<int> ll;
    std::deque<int> dd;

    print_result("empty vector throws", test_find_not_exists(vv, 0));
    print_result("empty list throws", test_find_not_exists(ll, 0));
    print_result("empty deque throws", test_find_not_exists(dd, 42));
}

static void test_single_element()
{
    std::vector<int> v;
    v.push_back(7);

    print_result("single element: found", test_find_exists(v, 7, 0));
    print_result("single element: not found throws", test_find_not_exists(v, 8));
}

static void test_duplicates_returns_first()
{
    std::vector<int> v;
    v.push_back(5);
    v.push_back(3);
    v.push_back(5);
    v.push_back(5);
    v.push_back(3);

    print_result("duplicates: returns FIRST occurrence of 5 (index 0)", test_find_exists(v, 5, 0));
    print_result("duplicates: returns FIRST occurrence of 3 (index 1)", test_find_exists(v, 3, 1));
}

static void test_negative_and_zero()
{
    std::vector<int> v;
    v.push_back(-100);
    v.push_back(0);
    v.push_back(-1);
    v.push_back(1);

    print_result("negative value found", test_find_exists(v, -100, 0));
    print_result("zero found", test_find_exists(v, 0, 1));
    print_result("negative -1 found", test_find_exists(v, -1, 2));
    print_result("negative not found throws", test_find_not_exists(v, -999));
}

static void test_extreme_int_values()
{
    std::vector<int> v;
    v.push_back(INT_MAX);
    v.push_back(INT_MIN);
    v.push_back(0);

    print_result("INT_MAX found", test_find_exists(v, INT_MAX, 0));
    print_result("INT_MIN found", test_find_exists(v, INT_MIN, 1));
    print_result("INT_MAX - 1 not found throws", test_find_not_exists(v, INT_MAX - 1));
    print_result("INT_MIN + 1 not found throws", test_find_not_exists(v, INT_MIN + 1));
}

static void test_list_and_deque()
{
    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    print_result("list: find element", test_find_exists(lst, 2, 1));
    print_result("list: not found throws", test_find_not_exists(lst, 99));

    std::deque<int> dq;
    dq.push_back(100);
    dq.push_back(200);
    dq.push_back(300);

    print_result("deque: find last element", test_find_exists(dq, 300, 2));
    print_result("deque: not found throws", test_find_not_exists(dq, 150));
}

static void test_const_overload()
{
    std::vector<int> v;
    v.push_back(11);
    v.push_back(22);
    v.push_back(33);

    const std::vector<int> &cv = v;

    print_result("const vector: find element", test_find_const(cv, 22, 1));
    print_result("const vector: not found throws", test_find_not_exists(cv, 44));

    const std::list<int> cl;
    // Nota: em C++98, inicializar const list diretamente é verboso,
    // usamos um vector auxiliar para popular se necessario, ou push_back num non-const e depois referenciamos como const.
    std::list<int> tmp;
    tmp.push_back(42);
    const std::list<int> &cl_ref = tmp;

    print_result("const list single element: found", test_find_const(cl_ref, 42, 0));
}

static void test_large_container()
{
    const int SIZE = 100000;
    std::vector<int> v;
    v.reserve(SIZE);
    for (int i = 0; i < SIZE; ++i)
        v.push_back(i);

    print_result("large vector: find first (0)", test_find_exists(v, 0, 0));
    print_result("large vector: find last (99999)", test_find_exists(v, SIZE - 1, SIZE - 1));
    print_result("large vector: find middle (50000)", test_find_exists(v, SIZE / 2, SIZE / 2));
    print_result("large vector: not found throws", test_find_not_exists(v, SIZE));
    print_result("large vector: negative not found throws", test_find_not_exists(v, -1));
}

static void test_all_same_elements()
{
    const int SIZE = 500;
    std::vector<int> v(SIZE, 42);

    print_result("all same: find 42 returns index 0", test_find_exists(v, 42, 0));
    print_result("all same: find 43 throws", test_find_not_exists(v, 43));
}

static void test_exception_what_message()
{
    std::vector<int> v;
    v.push_back(1);
    bool correct_message = false;

    try
    {
        easyfind(v, 999);
    }
    catch (const NotFoundException &e)
    {
        const char *msg = e.what();
        correct_message = (msg != 0) && (std::string(msg) == "Element not found");
    }
    catch (...)
    {
        correct_message = false;
    }

    print_result("exception what() returns correct message", correct_message);
}

static void test_exception_is_catchable_as_std_exception()
{
    std::vector<int> v;
    bool caught_as_std = false;

    try
    {
        easyfind(v, 1);
    }
    catch (const std::exception &)
    {
        caught_as_std = true;
    }
    catch (...)
    {
        caught_as_std = false;
    }

    print_result("NotFoundException catchable as std::exception", caught_as_std);
}

static void test_exception_ocf()
{
    bool passed = true;

    try
    {
        NotFoundException e1;
        NotFoundException e2(e1);
        NotFoundException e3;
        e3 = e2;
        /* e3 = e3; REMOVIDO: Evita -Werror,-Wself-assign-overloaded no Clang */
        (void)e3.what();
    }
    catch (...)
    {
        passed = false;
    }

    print_result("NotFoundException OCF: copy/assign/what safe", passed);
}

static void test_repeated_searches_same_container()
{
    const int SIZE = 1000;
    std::vector<int> v;
    v.reserve(SIZE);
    for (int i = 0; i < SIZE; ++i)
        v.push_back(i * 2);

    bool all_ok = true;
    for (int i = 0; i < SIZE; ++i)
    {
        if (!test_find_exists(v, i * 2, i))
        {
            all_ok = false;
            break;
        }
    }
    print_result("1000 repeated searches on same vector", all_ok);

    bool none_found = true;
    for (int i = 0; i < SIZE; ++i)
    {
        if (!test_find_not_exists(v, i * 2 + 1))
        {
            none_found = false;
            break;
        }
    }
    print_result("1000 repeated misses on same vector", none_found);
}

/* --------------------------------------------------------
 *  main
 * ------------------------------------------------------ */

int main()
{
    std::cout << BOLD << BRIGHT_CYAN << "=== easyfind test suite ===" << RESET << std::endl;
    std::cout << std::endl;

    test_vector_basic();
    test_empty_containers();
    test_single_element();
    test_duplicates_returns_first();
    test_negative_and_zero();
    test_extreme_int_values();
    test_list_and_deque();
    test_const_overload();
    test_large_container();
    test_all_same_elements();
    test_exception_what_message();
    test_exception_is_catchable_as_std_exception();
    test_exception_ocf();
    test_repeated_searches_same_container();

    std::cout << std::endl;
    std::cout << BOLD << "=== Results: "
              << GREEN << g_tests_passed << RESET << " passed, "
              << RED << g_tests_failed << RESET << " failed ===" << RESET << std::endl;

    if (g_tests_failed > 0)
        return 1;
    return 0;
}