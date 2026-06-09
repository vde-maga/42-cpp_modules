#include "Cat.hpp"
#include "Colors.hpp"

Cat::Cat(void) :
	Animal(), m_brain(new Brain())
{
	this->m_type = "Cat";
	std::cout << BRIGHT_YELLOW << "[Cat] Default constructor called"
		<< RESET << std::endl;
}

Cat::Cat(const Cat &other) :
	Animal(other), m_brain(new Brain(*other.m_brain))
{
	std::cout << BRIGHT_YELLOW << "[Cat] Copy constructor called"
		<< RESET << std::endl;
}

Cat::~Cat(void)
{
	delete this->m_brain;
	std::cout << BRIGHT_YELLOW << "[Cat] Destructor called"
		<< RESET << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
	std::cout << BRIGHT_YELLOW << "[Cat] Assignment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		Animal::operator=(other);
		*(this->m_brain) = *(other.m_brain);
	}
	return (*this);
}

void Cat::makeSound(void) const
{
	std::cout << BRIGHT_YELLOW << "* Meow! Meow! *"
		<< RESET << std::endl;
}

Brain *Cat::getBrain(void) const
{
	return (this->m_brain);
}
