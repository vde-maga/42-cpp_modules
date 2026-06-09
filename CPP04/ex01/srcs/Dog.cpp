#include "Dog.hpp"
#include "Colors.hpp"

Dog::Dog(void) :
	Animal(), m_brain(new Brain())
{
	this->m_type = "Dog";
	std::cout << BRIGHT_GREEN << "[Dog] Default constructor called"
		<< RESET << std::endl;
}

Dog::Dog(const Dog &other) :
	Animal(other), m_brain(new Brain(*other.m_brain))
{
	std::cout << BRIGHT_GREEN << "[Dog] Copy constructor called"
		<< RESET << std::endl;
}

Dog::~Dog(void)
{
	delete this->m_brain;
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
		*(this->m_brain) = *(other.m_brain);
	}
	return (*this);
}

void Dog::makeSound(void) const
{
	std::cout << BRIGHT_GREEN << "* Woof! Woof! *"
		<< RESET << std::endl;
}

Brain *Dog::getBrain(void) const
{
	return (this->m_brain);
}
