#include <iostream>
#include <string>
#include "../include/Iter.hpp"
#include "../include/Colors.hpp"

template <typename T>
void printElement(const T &elem)
{
	std::cout << elem << " ";
}

template <typename T>
void incrementElement(T &elem)
{
	++elem;
}

class MultiplyBy
{
private:
	int _factor;

public:
	explicit MultiplyBy(int factor) : _factor(factor) {}

	void operator()(int &elem) const
	{
		elem *= _factor;
	}
};

class CustomType
{
public:
	int value;
	std::string name;

	CustomType() : value(0), name("default") {}
	CustomType(int v, const std::string &n) : value(v), name(n) {}
	CustomType(const CustomType &other) : value(other.value), name(other.name) {}
	~CustomType() {}

	CustomType &operator=(const CustomType &other)
	{
		if (this != &other)
		{
			value = other.value;
			name = other.name;
		}
		return *this;
	}
};

std::ostream &operator<<(std::ostream &os, const CustomType &ct)
{
	os << "{" << ct.value << ", \"" << ct.name << "\"}";
	return os;
}


namespace TestUI
{
	void printHeader(const std::string &title)
	{
		std::cout << BOLD << BRIGHT_CYAN << "\n=== [TEST] " << title << " ===" << RESET << std::endl;
	}
	void printPass(const std::string &msg)
	{
		std::cout << BRIGHT_GREEN << "[PASS]" << RESET << " " << msg << std::endl;
	}
	void printFail(const std::string &msg)
	{
		std::cout << BRIGHT_RED << "[FAIL]" << RESET << " " << msg << std::endl;
	}
}


void test_basic_non_const()
{
	TestUI::printHeader("Basic Non-Const Array (Modification)");
	int arr[] = {1, 2, 3, 4, 5};
	const std::size_t len = sizeof(arr) / sizeof(arr[0]);

	::iter(arr, len, incrementElement<int>);

	bool success = (arr[0] == 2 && arr[4] == 6);
	if (success)
		TestUI::printPass("Elements incremented correctly");
	else
		TestUI::printFail("Elements not incremented");
}

void test_const_array()
{
	TestUI::printHeader("Const Array (Read-Only)");
	const std::string words[] = {"Hello", "World", "42"};
	const std::size_t len = sizeof(words) / sizeof(words[0]);

	std::cout << "Output: ";
	::iter(words, len, printElement<std::string>);
	std::cout << std::endl;
	TestUI::printPass("Const array iterated without compilation errors");
}

void test_functor_usage()
{
	TestUI::printHeader("Functor Usage (Advanced Callable)");
	int nums[] = {10, 20, 30};
	const std::size_t len = sizeof(nums) / sizeof(nums[0]);

	MultiplyBy doubler(2);
	::iter(nums, len, doubler);

	if (nums[0] == 20 && nums[1] == 40 && nums[2] == 60)
	{
		TestUI::printPass("Functor applied correctly");
	}
	else
	{
		TestUI::printFail("Functor failed to modify elements");
	}
}

void test_custom_type()
{
	TestUI::printHeader("Custom Orthodox Canonical Type");
	CustomType objs[] = {CustomType(1, "A"), CustomType(2, "B")};
	const std::size_t len = sizeof(objs) / sizeof(objs[0]);

	std::cout << "Before: ";
	::iter(objs, len, printElement<CustomType>);
	std::cout << std::endl;

	for (std::size_t i = 0; i < len; ++i)
	{
		objs[i].value *= 10;
	}

	std::cout << "After:  ";
	::iter(objs, len, printElement<CustomType>);
	std::cout << std::endl;

	if (objs[0].value == 10 && objs[1].value == 20)
	{
		TestUI::printPass("Custom type iterated and modified successfully");
	}
	else
	{
		TestUI::printFail("Custom type modification failed");
	}
}

void test_defensive_edge_cases() {
	TestUI::printHeader("Defensive Edge Cases (Null & Zero Length)");
	
	int valid_arr[] = {1, 2, 3};

	::iter(static_cast<int*>(NULL), 3, incrementElement<int>);
	::iter(valid_arr, 0, incrementElement<int>);
	::iter(static_cast<int*>(NULL), 0, incrementElement<int>);

	TestUI::printPass("Handled NULL and 0-length gracefully (No UB/Crash)");
}

int main()
{
	test_basic_non_const();
	test_const_array();
	test_functor_usage();
	test_custom_type();
	test_defensive_edge_cases();

	std::cout << BOLD << BRIGHT_GREEN << "\n[ALL EX01 TESTS COMPLETED SUCCESSFULLY]" << RESET << std::endl;
	return 0;
}
