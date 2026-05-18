#include "Animal.hpp"

Animal::Animal(void) : type("Animal") {
    std::cout << "[Animal] Default constructor called" << std::endl;
}

Animal::Animal(const Animal& other) : type(other.type) {
    std::cout << "[Animal] Copy constructor called" << std::endl;
}

Animal::~Animal(void) {
    std::cout << "[Animal] Destructor called" << std::endl;
}

Animal& Animal::operator=(const Animal& other) {
    std::cout << "[Animal] Assignment operator called" << std::endl;
    if (this != &other) {
        this->type = other.type;
    }
    return *this;
}

void Animal::makeSound(void) const {
    std::cout << "* Generic animal sound *" << std::endl;
}

const std::string& Animal::getType(void) const {
    return this->type;
}