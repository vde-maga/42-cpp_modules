#include "Colors.hpp"
#include "Replacer.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

// --- TDD Helper Functions (C++98 Strict, no C functions) ---

std::string readFileContent(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		return ("");
	std::ostringstream oss;
	oss << file.rdbuf();
	return (oss.str());
}

bool writeFileContent(const std::string &filename, const std::string &content)
{
	std::ofstream file(filename.c_str());
	if (!file.is_open())
		return false;
	file << content;
	return true;
}

// --- Automated Test Runner ---

void runTest(const std::string &testName, const std::string &input,
			 const std::string &search, const std::string &replace,
			 const std::string &expected, bool expectSuccess, bool &all_passed)
{
	bool success;
	bool passed;
	std::string output;

	const std::string inFile = "test_" + testName + ".txt";
	const std::string outFile = inFile + ".replace";

	writeFileContent(inFile, input);

	Replacer rep(inFile, search, replace);
	success = rep.execute();
	output = readFileContent(outFile);

	passed = (success == expectSuccess) && (output == expected);

	std::cout << MAGENTA << "Test: " << testName << RESET << std::endl;
	if (!passed)
	{
		std::cerr << RED << "  -> FAIL" << RESET << std::endl;
		std::cerr << YELLOW << "     Expected Success: " << (expectSuccess ? "True" : "False") << " | Got: " << (success ? "True" : "False") << RESET << std::endl;
		std::cerr << YELLOW << "     Expected Output: \"" << expected << "\" | Got: \"" << output << "\"" << RESET << std::endl;
		all_passed = false;
	}
	else
	{
		std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	}
	std::cout << std::endl;
}

// --- Test Execution ---

int runTests(void)
{
	bool all_passed = true;

	std::cout << "Starting Replacer unit tests" << std::endl
			  << std::endl;

	// Test 1: Basic Replacement
	runTest("Basic_Replacement", "Hello world, this is a test.", "world", "universe",
			"Hello universe, this is a test.", true, all_passed);

	// Test 2: Multiple Occurrences
	runTest("Multiple_Occurrences", "aaa bbb aaa ccc aaa", "aaa", "ddd",
			"ddd bbb ddd ccc ddd", true, all_passed);

	// Test 3: No Occurrence
	runTest("No_Occurrence", "Nothing to replace here.", "xxx", "yyy",
			"Nothing to replace here.", true, all_passed);

	// Test 4: Empty File
	runTest("Empty_File", "", "abc", "def", "", true, all_passed);

	// Test 5: Replace with Empty replace (Deletion)
	runTest("Delete_replace_Empty", "Remove this part", " this", "",
			"Remove part", true, all_passed);

	// Test 6: Adjacent Occurrences
	runTest("Adjacent_Occurrences", "catcat", "cat", "dog", "dogdog", true, all_passed);

	// Test 7: Substring Match (O "cat" dentro de "cats" DEVE ser substituído)
	runTest("Substring_Match", "I love cats", "cat", "dog", "I love dogs", true, all_passed);

	// Test 8: Empty search Should Fail (Defensive)
	runTest("Empty_search_Fail", "Some content", "", "replace", "", false, all_passed);

	// Test 9: Empty Filename Should Fail (Defensive - Must be done outside runTest)
	{
		std::cout << MAGENTA << "Test: Empty_Filename_Fail" << RESET << std::endl;
		bool passed = false;

		Replacer rep("", "a", "b");
		if (!rep.execute()) // Deve retornar false pois o filename está vazio
			passed = true;
		else
			all_passed = false;

		if (passed)
			std::cout << GREEN << "  -> PASS" << RESET << std::endl
					  << std::endl;
		else
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
	}

	// Test 10: Non Existent File Should Fail (Defensive - Must be done outside runTest)
	{
		std::cout << MAGENTA << "Test: Non_Existent_File" << RESET << std::endl;
		bool passed = false;

		Replacer rep("this_file_absolutely_does_not_exist_837492.txt", "a", "b");
		if (!rep.execute()) // Deve retornar false pois o ficheiro não existe
			passed = true;
		else
			all_passed = false;

		if (passed)
			std::cout << GREEN << "  -> PASS" << RESET << std::endl
					  << std::endl;
		else
			std::cout << RED << "  -> FAIL" << RESET << std::endl
					  << std::endl;
	}

	// Summary
	if (all_passed)
		std::cout << GREEN << "All Replacer tests passed!" << std::endl
				  << RESET;
	else
		std::cout << RED << "Some Replacer tests failed." << std::endl
				  << RESET;

	return (all_passed ? 0 : 1);
}

// --- Main Entry ---

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		return (runTests());
	}

	if (argc != 4)
	{
		std::cerr << RED << "Error: Invalid number of arguments." << std::endl
				  << "Usage: " << argv[0] << " <filename> <search> <replace>" << RESET << std::endl;
		return (1);
	}

	const std::string filename = argv[1];
	const std::string search = argv[2];
	const std::string replace = argv[3];

	if (search.empty())
	{
		std::cerr << RED << "Error: The string to be replaced (search) cannot be empty." << RESET << std::endl;
		return (1);
	}

	Replacer replacer(filename, search, replace);
	if (!replacer.execute())
	{
		std::cerr << RED << "Error: Failed to process the file replacement. Check file existence and permissions." << RESET << std::endl;
		return (1);
	}

	std::cout << GREEN << "Success: File processed and saved to " << filename << ".replace" << RESET << std::endl;
	return (0);
}
