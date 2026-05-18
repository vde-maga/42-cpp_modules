#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : type("WrongAnimal") {
    std::cout << "[WrongAnimal] Default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other) : type(other.type) {
    std::cout << "[WrongAnimal] Copy constructor called" << std::endl;
}

WrongAnimal::~WrongAnimal(void) {
    std::cout << "[WrongAnimal] Destructor called" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other) {
    std::cout << "[WrongAnimal] Assignment operator called" << std::endl;
    if (this != &other) {
        this->type = other.type;
    }
    return *this;
}

void WrongAnimal::makeSound(void) const {
    std::cout << "* WrongAnimal sound *" << std::endl;
}

const std::string& WrongAnimal::getType(void) const {
    return this->type;
}