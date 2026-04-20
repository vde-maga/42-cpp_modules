#include "replace.hpp"
#include <fstream>
#include <sstream>
#include <cstddef>

bool replaceInFile(const std::string& filename, const std::string& s1, const std::string& s2) {
    if (filename.empty() || s1.empty()) {
        return false;
    }

    std::ifstream inFile(filename.c_str());
    if (!inFile.is_open()) {
        return false;
    }

    std::ostringstream oss;
    oss << inFile.rdbuf();
    if (!inFile.good() && !inFile.eof()) {
        return false;
    }
    inFile.close();

    const std::string content = oss.str();
    std::string result;
    result.reserve(content.size());

    std::size_t pos = 0;
    std::size_t prev = 0;

    while ((pos = content.find(s1, prev)) != std::string::npos) {
        result.append(content, prev, pos - prev);
        result.append(s2);
        prev = pos + s1.size();
    }
    result.append(content, prev, std::string::npos);

    const std::string outFilename = filename + ".replace";
    std::ofstream outFile(outFilename.c_str());
    if (!outFile.is_open()) {
        return false;
    }

    outFile << result;
    if (!outFile.good()) {
        outFile.close();
        return false;
    }

    return true;
}
