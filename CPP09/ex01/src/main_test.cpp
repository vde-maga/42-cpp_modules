#include "../include/RPN.hpp"
#include "../include/Colors.hpp"
#include <iostream>
#include <sstream>

void runTest(const std::string &testName, const std::string &input, const std::string &expectedOutput)
{
    // Redireciona stdout e stderr para capturar a saída
    std::streambuf *oldCout = std::cout.rdbuf();
    std::streambuf *oldCerr = std::cerr.rdbuf();
    std::stringstream bufferOut;
    std::stringstream bufferErr;
    std::cout.rdbuf(bufferOut.rdbuf());
    std::cerr.rdbuf(bufferErr.rdbuf());

    try
    {
        RPN rpn(input);
        rpn.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    // Restaura stdout e stderr
    std::cout.rdbuf(oldCout);
    std::cerr.rdbuf(oldCerr);

    // Combina stdout e stderr para verificação (erros vão para stderr)
    std::string actualOutput = bufferOut.str() + bufferErr.str();

    if (actualOutput == expectedOutput)
    {
        std::cout << BRIGHT_GREEN << BOLD << "[PASS] " << RESET << testName << std::endl;
    }
    else
    {
        std::cout << BRIGHT_RED << BOLD << "[FAIL] " << RESET << testName << std::endl;
        std::cout << YELLOW << "  Expected: " << RESET << expectedOutput;
        std::cout << YELLOW << "  Actual:   " << RESET << actualOutput;
        std::cout << CYAN << "  ----------------------------------------\n"
                  << RESET;
    }
}

int main()
{
    std::cout << BOLD << UNDERLINE << "Iniciando Suite de Testes RPN..." << RESET << "\n\n";

    // Testes do Subject
    runTest("Subject Example 1", "8 9 * 9 - 9 - 9 - 4 - 1 +", "42\n");
    runTest("Subject Example 2", "7 7 * 7 -", "42\n");
    runTest("Subject Example 3", "1 2 * 2 / 2 * 2 4 - +", "0\n");
    runTest("Subject Error Example", "(1 + 1)", "Error\n");

    // Testes Extremos de Erro
    runTest("Division by Zero", "1 0 /", "Error\n");
    runTest("Not Enough Numbers", "1 +", "Error\n");
    runTest("Not Enough Operators", "1 2", "Error\n");
    runTest("Too Many Operators", "1 2 + +", "Error\n");
    runTest("Invalid Character", "1 2 + a", "Error\n");
    runTest("Empty Input", "", "Error\n");
    runTest("Only Spaces", "   ", "Error\n");
    runTest("Multiple Spaces", "1   2   +", "3\n");

    // Testes de Lógica
    runTest("Complex Valid Expression", "5 1 2 + 4 * + 3 -", "14\n");
    runTest("Negative Result", "1 2 -", "-1\n");
    runTest("Division Truncation", "5 2 /", "2\n"); // 5 / 2 = 2 (integer division)
    runTest("Zero Result", "0 0 +", "0\n");

    std::cout << "\n"
              << BOLD << "Testes Concluídos." << RESET << std::endl;
    return 0;
}
