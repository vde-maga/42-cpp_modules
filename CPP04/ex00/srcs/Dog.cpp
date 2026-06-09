#include "Colors.hpp"
#include "Dog.hpp"

Dog::Dog(void) : Animal()
{
	this->m_type = "Dog";

	std::cout << BRIGHT_GREEN << "[Dog] Default constructor called"
		<< RESET << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other)
{
	std::cout << BRIGHT_GREEN << "[Dog] Copy constructor called"
		<< RESET << std::endl;
}

Dog::~Dog(void)
{
	std::cout << BRIGHT_GREEN << "[Dog] Destructor called"
		<< RESET << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
	std::cout << BRIGHT_GREEN << "[Dog] Assignment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		Animal::operator=(other);
	}
	return (*this);
}

void Dog::makeSound(void) const
{
	std::cout << BRIGHT_GREEN << "* Woof! Woof! *"
		<< RESET << std::endl;
}
