#ifndef REPLACER_HPP
#define REPLACER_HPP

#include <string>
#include <fstream>

class Replacer {
public:
    Replacer(const std::string& filename, const std::string& s1, const std::string& s2);
    ~Replacer();

    // Executa a operação de leitura, substituição e escrita.
    // Retorna false em caso de erro (Defensive Error Handling).
    bool execute() const;

private:
    const std::string _filename;
    const std::string _s1;
    const std::string _s2;

    // Função helper que faz a substituição na string (KISS / DRY)
    std::string _replaceString(const std::string& content) const;

    // Prevenção de cópias acidentais (SOLID / C++ Idioms)
    Replacer(const Replacer&);
    Replacer& operator=(const Replacer&);
};

#endif // REPLACER_HPP