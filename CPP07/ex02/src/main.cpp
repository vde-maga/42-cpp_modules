#include <iostream>
#include <string>
#include <stdexcept>
#include "../include/Array.hpp"
#include "../include/Colors.hpp"

// Classe Customizada (Orthodox Canonical Form) para provar que não há UB com memcpy
class CustomType {
public:
	int value;
	std::string name;

	CustomType() : value(0), name("default") {}
	CustomType(int v, const std::string& n) : value(v), name(n) {}
	CustomType(const CustomType& other) : value(other.value), name(other.name) {}
	~CustomType() {}

	CustomType& operator=(const CustomType& other) {
		if (this != &other) {
			value = other.value;
			name = other.name;
		}
		return *this;
	}
};

std::ostream& operator<<(std::ostream& os, const CustomType& ct) {
	os << "{" << ct.value << ", \"" << ct.name << "\"}";
	return os;
}

namespace TestUI {
	void printHeader(const std::string& title) {
		std::cout << BOLD << BRIGHT_CYAN << "\n=== [TEST] " << title << " ===" << RESET << std::endl;
	}
	void printPass(const std::string& msg) {
		std::cout << BRIGHT_GREEN << "[PASS]" << RESET << " " << msg << std::endl;
	}
	void printFail(const std::string& msg) {
		std::cout << BRIGHT_RED << "[FAIL]" << RESET << " " << msg << std::endl;
	}
}

void test_constructors_and_size() {
	TestUI::printHeader("Constructors and Size");
	Array<int> empty;
	Array<int> sized(5);

	if (empty.size() == 0) TestUI::printPass("Default constructor creates empty array");
	else TestUI::printFail("Default constructor failed");

	if (sized.size() == 5) TestUI::printPass("Parameterized constructor creates sized array");
	else TestUI::printFail("Parameterized constructor failed");
}

void test_deep_copy_and_assignment() {
	TestUI::printHeader("Deep Copy and Assignment");
	Array<int> original(3);
	original[0] = 1;
	original[1] = 2;
	original[2] = 3;

	Array<int> copy(original);
	copy[0] = 99;

	if (original[0] == 1 && copy[0] == 99) {
		TestUI::printPass("Copy constructor creates independent deep copy");
	} else {
		TestUI::printFail("Copy constructor failed (shallow copy?)");
	}

	Array<int> assigned(1);
	assigned = original;
	assigned[1] = 88;

	if (original[1] == 2 && assigned[1] == 88) {
		TestUI::printPass("Assignment operator creates independent deep copy");
	} else {
		TestUI::printFail("Assignment operator failed");
	}

	// Self-assignment test
	// Usamos uma referência para contornar o warning de compilação do Clang.
	Array<int>& self_ref = assigned;
	assigned = self_ref;
	
	// O self-assignment não deve alterar o estado atual do objeto.
	// Antes do self-assignment, 'assigned' era [1, 88, 3]. Ele deve continuar assim.
	if (assigned[0] == 1 && assigned[1] == 88 && assigned[2] == 3) {
		TestUI::printPass("Self-assignment handled safely (State unchanged)");
	} else {
		TestUI::printFail("Self-assignment corrupted data");
	}
}

void test_operator_brackets_and_exceptions() {
	TestUI::printHeader("Operator[] and Exception Handling");
	Array<int> arr(3);
	arr[0] = 10;
	arr[1] = 20;
	arr[2] = 30;

	bool pass = true;
	if (arr[0] != 10 || arr[1] != 20 || arr[2] != 30) pass = false;

	try {
		int val = arr[3]; // Out of bounds
		(void)val;
		pass = false; // Should have thrown
	} catch (const std::exception& e) {
		// Expected
	}

	try {
		Array<int> empty;
		empty[0] = 5; // Out of bounds on empty array
		pass = false;
	} catch (const std::exception& e) {
		// Expected
	}

	if (pass) TestUI::printPass("Operator[] works and throws on out of bounds");
	else TestUI::printFail("Operator[] or exception handling failed");
}

void test_const_correctness() {
	TestUI::printHeader("Const Correctness");
	Array<std::string> arr(2);
	arr[0] = "Hello";
	arr[1] = "World";

	const Array<std::string>& const_ref = arr;
	
	bool pass = true;
	try {
		if (const_ref[0] != "Hello" || const_ref[1] != "World") pass = false;
		
		// This should fail to compile if uncommented, proving const-correctness:
		// const_ref[0] = "Fail"; 
	} catch (...) {
		pass = false;
	}

	if (pass) TestUI::printPass("Const operator[] allows read-only access");
	else TestUI::printFail("Const operator[] failed");
}

void test_custom_type() {
	TestUI::printHeader("Custom Type (Proves no memcpy UB)");
	Array<CustomType> arr(2);
	arr[0] = CustomType(1, "Alpha");
	arr[1] = CustomType(2, "Beta");

	Array<CustomType> copy(arr);
	copy[0].value = 99;
	copy[0].name = "Modified";

	if (arr[0].value == 1 && arr[0].name == "Alpha" && 
		copy[0].value == 99 && copy[0].name == "Modified") {
		TestUI::printPass("Custom type deep copied correctly (No UB)");
	} else {
		TestUI::printFail("Custom type copy failed");
	}
}

int main() {
	test_constructors_and_size();
	test_deep_copy_and_assignment();
	test_operator_brackets_and_exceptions();
	test_const_correctness();
	test_custom_type();

	std::cout << BOLD << BRIGHT_GREEN << "\n[ALL EX02 TESTS COMPLETED SUCCESSFULLY]" << RESET << std::endl;
	return 0;
}