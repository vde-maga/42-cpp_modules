#include "Replacer.hpp"
#include <sstream>

Replacer::Replacer(const std::string& filename, const std::string& s1, const std::string& s2)
    : _filename(filename), _s1(s1), _s2(s2) {}

Replacer::~Replacer() {}

bool Replacer::execute() const {
    // Defensivo: s1 vazio causa loop infinito em find ou comportamento indefinido.
    if (_s1.empty()) {
        return false;
    }

    // RAII: O arquivo é aberto e será fechado automaticamente ao sair do escopo.
    std::ifstream inFile(_filename.c_str());
    if (!inFile.is_open() || inFile.fail()) {
        return false;
    }

    // Lê o arquivo inteiro para memória usando stringstream (Idiomatic C++)
    std::ostringstream oss;
    oss << inFile.rdbuf();
    
    // Verifica falha na leitura (Defensive Error Handling)
    if (inFile.fail() && !inFile.eof()) {
        return false;
    }
    inFile.close(); // Explicit close, mas o destrutor cuidaria se esquecêssemos (RAII)

    std::string content = oss.str();
    std::string replacedContent = _replaceString(content);

    std::string outFilename = _filename + ".replace";
    std::ofstream outFile(outFilename.c_str());
    if (!outFile.is_open() || outFile.fail()) {
        return false;
    }

    outFile << replacedContent;
    if (outFile.fail()) {
        return false;
    }

    return true;
}

std::string Replacer::_replaceString(const std::string& content) const {
    std::string result;
    size_t pos = 0;
    size_t prevPos = 0;

    // Reserva espaço estimado para evitar realocações frequentes (Boa prática)
    result.reserve(content.size());

    while ((pos = content.find(_s1, pos)) != std::string::npos) {
        // Adiciona o conteúdo antes da ocorrência
        result.append(content.substr(prevPos, pos - prevPos));
        // Adiciona a string substituta
        result.append(_s2);
        
        // Move os cursores para frente
        pos += _s1.length();
        prevPos = pos;
    }

    // Adiciona o restante do arquivo após a última ocorrência
    result.append(content.substr(prevPos));
    
    return result;
}
