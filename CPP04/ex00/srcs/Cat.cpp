#include "Cat.hpp"

Cat::Cat(void) : Animal() {
    this->type = "Cat";
    std::cout << "[Cat] Default constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
    std::cout << "[Cat] Copy constructor called" << std::endl;
}

Cat::~Cat(void) {
    std::cout << "[Cat] Destructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "[Cat] Assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
    }
    return *this;
}

void Cat::makeSound(void) const {
    std::cout << "* Meow! Meow! *" << std::endl;
}