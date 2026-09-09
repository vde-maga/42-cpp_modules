#include "../include/BitcoinExchange.hpp"
#include "../include/Colors.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iostream>

void createFile(const std::string &filename, const std::string &content)
{
    std::ofstream ofs(filename.c_str());
    ofs << content;
}

void runTest(const std::string &testName, const std::string &dbContent, const std::string &inputContent, const std::string &expectedOutput)
{
    createFile("data.csv", dbContent);
    createFile("test_input.txt", inputContent);

    // Redireciona cout para capturar a saída
    std::streambuf *oldCout = std::cout.rdbuf();
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());

    try
    {
        BitcoinExchange btc;
        btc.execute("test_input.txt");
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    // Restaura cout
    std::cout.rdbuf(oldCout);
    std::string actualOutput = buffer.str();

    // Comparação e Output Colorido
    if (actualOutput == expectedOutput)
    {
        std::cout << BRIGHT_GREEN << BOLD << "[PASS] " << RESET << testName << std::endl;
    }
    else
    {
        std::cout << BRIGHT_RED << BOLD << "[FAIL] " << RESET << testName << std::endl;
        std::cout << YELLOW << "  Expected:\n"
                  << RESET << expectedOutput;
        std::cout << YELLOW << "  Actual:\n"
                  << RESET << actualOutput;
        std::cout << CYAN << "  ----------------------------------------\n"
                  << RESET;
    }

    std::remove("data.csv");
    std::remove("test_input.txt");
}

int main()
{
    std::cout << BOLD << UNDERLINE << "Iniciando Suite de Testes Bitcoin Exchange..." << RESET << "\n\n";

    std::string db = "date,exchange_rate\n2011-01-03,0.3\n2011-01-05,0.5\n2012-01-11,7.1\n2000-02-28,1.0\n";

    // 1. Teste Básico e Busca de Data Inferior (upper_bound)
    runTest("Basic & Lower Bound Search", db,
            "date | value\n2011-01-03 | 3\n2011-01-04 | 2\n",
            "2011-01-03 => 3 = 0.9\n2011-01-04 => 2 = 0.6\n");

    // 2. Limites Exatos de Valor (0 e 1000)
    runTest("Value Boundaries (0 and 1000)", db,
            "date | value\n2011-01-03 | 0\n2011-01-03 | 1000\n",
            "2011-01-03 => 0 = 0\n2011-01-03 => 1000 = 300\n");

    // 3. Erros de Valor (Negativo e > 1000)
    runTest("Value Errors (Negative & >1000)", db,
            "date | value\n2011-01-03 | -0.01\n2011-01-03 | 1000.01\n",
            "Error: not a positive number.\nError: too large a number.\n");

    // 4. Erros de Formato e Data Inválida
    runTest("Format & Invalid Date Errors", db,
            "date | value\n2001-42-42\n2011-01-03 | abc\n2011-01-03 3\n",
            "Error: bad input => 2001-42-42\nError: bad input => abc\nError: bad input => 2011-01-03 3\n");

    // 5. Teste de Ano Bissexto (2000 é bissexto, 1900 não é)
    std::string dbLeap = "date,exchange_rate\n2000-02-29,5.0\n1900-02-28,2.0\n";
    runTest("Leap Year Logic", dbLeap,
            "date | value\n2000-02-29 | 2\n1900-02-29 | 2\n",
            "2000-02-29 => 2 = 10\nError: bad input => 1900-02-29\n");

    // 6. Data Menor que a Primeira do DB (Deve usar a primeira disponível)
    runTest("Date Lower Than DB Start", db,
            "date | value\n2000-01-01 | 10\n",
            "2000-01-01 => 10 = 10\n"); // Pega 2000-02-28 (rate 1.0)

    // 7. Data Maior que a Última do DB (Deve usar a última disponível)
    runTest("Date Higher Than DB End", db,
            "date | value\n2025-12-31 | 5\n",
            "2025-12-31 => 5 = 35.5\n"); // Pega 2012-01-11 (rate 7.1)

    // 8. Header Errado no Input (Deve processar como linha normal e dar erro de formato)
    runTest("Wrong Header Handling", db,
            "wrong header\n2011-01-03 | 3\n",
            "Error: bad input => wrong header\n2011-01-03 => 3 = 0.9\n");

    // 9. Erro de Abertura de Arquivo (FileError)
    createFile("data.csv", db); // Recria o DB para o construtor não falhar
    std::streambuf *oldCout = std::cout.rdbuf();
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());

    try
    {
        BitcoinExchange btc;
        btc.execute("non_existent_file.txt"); // Aqui deve lançar FileError
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout.rdbuf(oldCout);
    std::remove("data.csv"); // Limpa novamente após o teste

    if (buffer.str().find("Error: could not open file.") != std::string::npos)
    {
        std::cout << BRIGHT_GREEN << BOLD << "[PASS] " << RESET << "File Open Error Exception" << std::endl;
    }
    else
    {
        std::cout << BRIGHT_RED << BOLD << "[FAIL] " << RESET << "File Open Error Exception" << std::endl;
        std::cout << YELLOW << "  Expected to find: Error: could not open file.\n"
                  << RESET;
        std::cout << YELLOW << "  Actual buffer:\n"
                  << RESET << buffer.str();
    }

    std::cout << "\n"
              << BOLD << "Testes Concluídos." << RESET << std::endl;
    return 0;
}
