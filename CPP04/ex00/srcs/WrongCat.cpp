#include "WrongCat.hpp"

WrongCat::WrongCat(void) : WrongAnimal() {
    this->type = "WrongCat";
    std::cout << "[WrongCat] Default constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other) {
    std::cout << "[WrongCat] Copy constructor called" << std::endl;
}

WrongCat::~WrongCat(void) {
    std::cout << "[WrongCat] Destructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other) {
    std::cout << "[WrongCat] Assignment operator called" << std::endl;
    if (this != &other) {
        WrongAnimal::operator=(other);
    }
    return *this;
}

void WrongCat::makeSound(void) const {
    std::cout << "* Mrrrrr! *" << std::endl;
}