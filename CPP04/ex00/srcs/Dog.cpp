#include "Dog.hpp"

Dog::Dog(void) : Animal() {
    this->type = "Dog";
    std::cout << "[Dog] Default constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "[Dog] Copy constructor called" << std::endl;
}

Dog::~Dog(void) {
    std::cout << "[Dog] Destructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "[Dog] Assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
    }
    return *this;
}

void Dog::makeSound(void) const {
    std::cout << "* Woof! Woof! *" << std::endl;
}