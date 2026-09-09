#include "../include/PmergeMe.hpp"
#include "../include/Colors.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

void runTest(const std::string& testName, const std::vector<int>& input, const std::vector<int>& expectedSorted, bool expectError = false) {
    std::streambuf* oldCout = std::cout.rdbuf();
    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::stringstream bufferOut;
    std::stringstream bufferErr;
    std::cout.rdbuf(bufferOut.rdbuf());
    std::cerr.rdbuf(bufferErr.rdbuf());

    bool errorCaught = false;
    try {
        PmergeMe pm(input);
        pm.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        errorCaught = true;
    }

    std::cout.rdbuf(oldCout);
    std::cerr.rdbuf(oldCerr);

    std::string actualOut = bufferOut.str();
    std::string actualErr = bufferErr.str();

    bool passed = false;
    if (expectError) {
        passed = errorCaught && actualErr.find("Error") != std::string::npos;
    } else {
        // Verifica se o "After:" contém a sequência esperada
        std::stringstream expectedAfter;
        expectedAfter << "After: ";
        for (size_t i = 0; i < expectedSorted.size(); ++i) {
            if (i > 0) expectedAfter << " ";
            expectedAfter << expectedSorted[i];
        }
        passed = !errorCaught && actualOut.find(expectedAfter.str()) != std::string::npos;
    }

    if (passed) {
        std::cout << BRIGHT_GREEN << BOLD << "[PASS] " << RESET << testName << std::endl;
    } else {
        std::cout << BRIGHT_RED << BOLD << "[FAIL] " << RESET << testName << std::endl;
        std::cout << YELLOW << "  Expected Error: " << RESET << (expectError ? "Yes" : "No") << std::endl;
        std::cout << YELLOW << "  Actual Output:\n" << RESET << actualOut << actualErr;
        std::cout << CYAN << "  ----------------------------------------\n" << RESET;
    }
}

int main() {
    std::cout << BOLD << UNDERLINE << "Iniciando Suite de Testes PmergeMe..." << RESET << "\n\n";

    // Testes Básicos
    std::vector<int> v1; v1.push_back(3); v1.push_back(5); v1.push_back(9); v1.push_back(7); v1.push_back(4);
    std::vector<int> e1; e1.push_back(3); e1.push_back(4); e1.push_back(5); e1.push_back(7); e1.push_back(9);
    runTest("Subject Example", v1, e1);

    // Teste com Duplicatas (O subject deixa a nosso critério, nosso código aceita e ordena corretamente)
    std::vector<int> v2; v2.push_back(5); v2.push_back(2); v2.push_back(5); v2.push_back(1);
    std::vector<int> e2; e2.push_back(1); e2.push_back(2); e2.push_back(5); e2.push_back(5);
    runTest("Duplicates Handling", v2, e2);

    // Teste com Número Ímpar de Elementos
    std::vector<int> v3; v3.push_back(10); v3.push_back(1); v3.push_back(5);
    std::vector<int> e3; e3.push_back(1); e3.push_back(5); e3.push_back(10);
    runTest("Odd Number of Elements", v3, e3);

    // Teste com 1 Elemento
    std::vector<int> v4; v4.push_back(42);
    std::vector<int> e4; e4.push_back(42);
    runTest("Single Element", v4, e4);

    // Teste com 2 Elementos
    std::vector<int> v5; v5.push_back(9); v5.push_back(1);
    std::vector<int> e5; e5.push_back(1); e5.push_back(9);
    runTest("Two Elements", v5, e5);

    // Teste de Performance (3000 elementos)
    std::vector<int> v6;
    for (int i = 3000; i > 0; --i) v6.push_back(i); // Pior caso: ordem inversa
    std::vector<int> e6;
    for (int i = 1; i <= 3000; ++i) e6.push_back(i);
    runTest("3000 Elements (Reverse Order)", v6, e6);

    std::cout << "\n" << BOLD << "Testes Concluídos." << RESET << std::endl;
    return 0;
}
