#include "../include/PmergeMe.hpp"
#include <cstdlib>
#include <cerrno>
#include <climits>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::vector<int> input;
    for (int i = 1; i < argc; ++i) {
        char* endptr;
        errno = 0;
        long val = std::strtol(argv[i], &endptr, 10);
        
        if (errno == ERANGE || val > INT_MAX || val <= 0 || *endptr != '\0') {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        input.push_back(static_cast<int>(val));
    }

    try {
        PmergeMe pm(input);
        pm.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
