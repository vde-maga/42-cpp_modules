#include "Harl.hpp"
#include <cstdlib>
#include <iostream>

void run_test(Harl& harl, const std::string& level) {
    std::cout << "[ Testing level: " << level << " ]" << std::endl;
    harl.complain(level);
    std::cout << std::endl;
}

int main() {
    Harl harl;

    run_test(harl, "DEBUG");
    run_test(harl, "INFO");
    run_test(harl, "WARNING");
    run_test(harl, "ERROR");
    run_test(harl, "INVALID_LEVEL");
    run_test(harl, "");
    run_test(harl, "debug");

    return 0;
}
