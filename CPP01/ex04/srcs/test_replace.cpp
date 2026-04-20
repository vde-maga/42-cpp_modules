// File: test_replace.cpp
#include "test_replace.hpp"
#include "replace.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstdlib>

namespace {

bool createFile(const std::string& name, const std::string& content) {
    std::ofstream out(name.c_str());
    if (!out.is_open()) return false;
    out << content;
    return out.good();
}

std::string readFile(const std::string& name) {
    std::ifstream in(name.c_str());
    if (!in.is_open()) return "";
    std::ostringstream oss;
    oss << in.rdbuf();
    return oss.str();
}

void removeFile(const std::string& name) {
    std::remove(name.c_str());
}

void testBasicReplace() {
    const std::string inFile = "test_basic.txt";
    const std::string outFile = "test_basic.txt.replace";
    createFile(inFile, "hello world hello");
    assert(replaceInFile(inFile, "hello", "hi") == true);
    assert(readFile(outFile) == "hi world hi");
    removeFile(inFile);
    removeFile(outFile);
    std::cout << "[PASS] testBasicReplace" << std::endl;
}

void testNoMatch() {
    const std::string inFile = "test_nomatch.txt";
    const std::string outFile = "test_nomatch.txt.replace";
    createFile(inFile, "hello world");
    assert(replaceInFile(inFile, "foo", "bar") == true);
    assert(readFile(outFile) == "hello world");
    removeFile(inFile);
    removeFile(outFile);
    std::cout << "[PASS] testNoMatch" << std::endl;
}

void testEmptyS1() {
    assert(replaceInFile("dummy.txt", "", "replace") == false);
    std::cout << "[PASS] testEmptyS1" << std::endl;
}

void testNonExistentFile() {
    assert(replaceInFile("nonexistent_file_12345.txt", "a", "b") == false);
    std::cout << "[PASS] testNonExistentFile" << std::endl;
}

void testOverlappingMatches() {
    const std::string inFile = "test_overlap.txt";
    const std::string outFile = "test_overlap.txt.replace";
    createFile(inFile, "aaa");
    assert(replaceInFile(inFile, "aa", "b") == true);
    assert(readFile(outFile) == "ba");
    removeFile(inFile);
    removeFile(outFile);
    std::cout << "[PASS] testOverlappingMatches" << std::endl;
}

void testEmptyFile() {
    const std::string inFile = "test_empty.txt";
    const std::string outFile = "test_empty.txt.replace";
    createFile(inFile, "");
    assert(replaceInFile(inFile, "a", "b") == true);
    assert(readFile(outFile) == "");
    removeFile(inFile);
    removeFile(outFile);
    std::cout << "[PASS] testEmptyFile" << std::endl;
}

void testReplaceWithEmpty() {
    const std::string inFile = "test_replempty.txt";
    const std::string outFile = "test_replempty.txt.replace";
    createFile(inFile, "abcabc");
    assert(replaceInFile(inFile, "abc", "") == true);
    assert(readFile(outFile) == "");
    removeFile(inFile);
    removeFile(outFile);
    std::cout << "[PASS] testReplaceWithEmpty" << std::endl;
}

void testMultipleLines() {
    const std::string inFile = "test_multiline.txt";
    const std::string outFile = "test_multiline.txt.replace";
    createFile(inFile, "line1\nline2\nline3");
    assert(replaceInFile(inFile, "line", "row") == true);
    assert(readFile(outFile) == "row1\nrow2\nrow3");
    removeFile(inFile);
    removeFile(outFile);
    std::cout << "[PASS] testMultipleLines" << std::endl;
}

} // anonymous namespace

void runTests() {
    testBasicReplace();
    testNoMatch();
    testEmptyS1();
    testNonExistentFile();
    testOverlappingMatches();
    testEmptyFile();
    testReplaceWithEmpty();
    testMultipleLines();
}
