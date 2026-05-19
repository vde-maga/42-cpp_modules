#include "Colors.hpp"
#include "Replacer.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

// --- TDD Helper Functions ---

std::string readFileContent(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		return ("[FILE NOT FOUND OR UNREADABLE]");
	std::ostringstream oss;
	oss << file.rdbuf();
	return (oss.str());
}

void	writeFileContent(const std::string &filename,
		const std::string &content)
{
	std::ofstream file(filename.c_str());
	if (file.is_open())
	{
		file << content;
	}
}

void	cleanFile(const std::string &filename)
{
	std::remove(filename.c_str());
}

void	printVisual(const std::string &label, const std::string &content,
		const std::string &color)
{
	std::cout << color << label << ": \"" << content << "\"" << RESET << std::endl;
}

// --- Visual Test Runners ---

void	runVisualTest(const std::string &testName, const std::string &input,
		const std::string &s1, const std::string &s2,
		const std::string &expected, bool expectSuccess = true)
{
	bool	success;
	bool	passed;

	const std::string inFile = "test_" + testName + ".txt";
	const std::string outFile = inFile + ".replace";
	writeFileContent(inFile, input);
	Replacer rep(inFile, s1, s2);
	success = rep.execute();
	std::string output = readFileContent(outFile);
	std::cout << BOLDCYAN << "TEST: " << testName << RESET << std::endl;
	printVisual("Find (s1) ", s1, YELLOW);
	printVisual("Replace (s2)", s2, YELLOW);
	printVisual("Entry", input, WHITE);
	printVisual("Expected", expected, MAGENTA);
	printVisual("Result", output, (output == expected ? GREEN : RED));
	passed = (success == expectSuccess) && (output == expected);
	std::cout << "----------" << std::endl;
	if (passed)
	{
		std::cout << BOLDGREEN << "[PASS]" << RESET << std::endl;
	}
	else
	{
		std::cout << BOLDRED << "[FAIL]" << RESET << std::endl;
		std::cout << RED << " -> Expected Success?: " << (expectSuccess ? "Yes" : "No") << " | Success?: " << (success ? "Yes" : "No") << RESET << std::endl;
	}
	std::cout << std::endl;
	cleanFile(inFile);
	cleanFile(outFile);
}

void	runFailureTest(const std::string &testName, const std::string &filename,
		const std::string &s1, const std::string &s2)
{
	bool	success;

	Replacer rep(filename, s1, s2);
	success = rep.execute();
	std::cout << BOLDCYAN << "DEFENSIVE TEST: " << testName << RESET << std::endl;
	printVisual("File", filename, WHITE);
	printVisual("Find", s1, YELLOW);
	std::cout << "----------" << std::endl;
	if (!success)
	{
		std::cout << BOLDGREEN << "[PASS]" << RESET << "Program didnt crash" << std::endl;
	}
	else
	{
		std::cout << BOLDRED << "[FAIL]" << RESET << " O programa permitiu uma operação ilegal." << std::endl;
	}
	std::cout << std::endl;
}

// --- Test Cases ---

void	testBasicReplacement(void)
{
	runVisualTest("Basico", "Hello world, this is a test.", "world", "universe",
		"Hello universe, this is a test.");
}

void	testMultipleOccurrences(void)
{
	runVisualTest("Multiplas_Ocorrencias", "aaa bbb aaa ccc aaa", "aaa", "ddd",
		"ddd bbb ddd ccc ddd");
}

void	testNoOccurrence(void)
{
	runVisualTest("Sem_Ocorrencia", "Nothing to replace here.", "xxx", "yyy",
		"Nothing to replace here.");
}

void	testEmptyFile(void)
{
	runVisualTest("Arquivo_Vazio", "", "abc", "def", "");
}

void	testReplaceWithEmptyS2(void)
{
	runVisualTest("Delecao_s2_Vazio", "Remove this part", " this", "",
		"Remove part");
}

void	testAdjacentOccurrences(void)
{
	runVisualTest("Ocorrencias_Adjacentes", "catcat", "cat", "dog", "dogdog");
}

void	testPartialMatchShouldNotReplace(void)
{
	runVisualTest("Match_Parcial", "I love cats", "cat", "dog", "I love cats");
}

void	testEmptyS1ShouldFail(void)
{
	cleanFile("test_s1_vazio.txt");
	writeFileContent("test_s1_vazio.txt", "Some content");
	runFailureTest("s1_Vazio", "test_s1_vazio.txt", "", "replace");
	cleanFile("test_s1_vazio.txt");
	cleanFile("test_s1_vazio.txt.replace");
}

void	testNonExistentFileShouldFail(void)
{
	runFailureTest("Arquivo_Inexistente", "arquivo_que_nao_existe_12345.txt",
		"a", "b");
}

void	runTests(void)
{
	std::cout << BOLDMAGENTA << "--- Sed Tests ---" << RESET << std::endl;
	testBasicReplacement();
	testMultipleOccurrences();
	testNoOccurrence();
	testEmptyFile();
	testReplaceWithEmptyS2();
	testAdjacentOccurrences();
	testPartialMatchShouldNotReplace();
	testEmptyS1ShouldFail();
	testNonExistentFileShouldFail();
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		runTests();
		return (0);
	}

	if (argc != 4)
	{
		std::cerr << BOLDRED << "Error: Invalid number of arguments." << std::endl
			<< "Usage: " << argv[0] << " <filename> <s1> <s2>" << RESET << std::endl;
		return (1);
	}
	const std::string filename = argv[1];
	const std::string s1 = argv[2];
	const std::string s2 = argv[3];
	if (s1.empty())
	{
		std::cerr << BOLDRED <<
			"Error: The string to be replaced (s1) cannot be empty." << RESET << std::endl;
		return (1);
	}
	Replacer replacer(filename, s1, s2);
	if (!replacer.execute())
	{
		std::cerr << BOLDRED <<
			"Error: Failed to process the file replacement. Check file existence and permissions." << RESET << std::endl;
		return (1);
	}
	std::cout << BOLDGREEN << "Success: File processed and saved to " << filename << ".replace" << RESET << std::endl;
	return (0);
}
