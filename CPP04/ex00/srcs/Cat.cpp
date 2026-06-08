#include "Cat.hpp"
#include "Colors.hpp"

Cat::Cat(void) : Animal()
{
	this->type = "Cat";
	std::cout << BRIGHT_YELLOW << "[Cat] Default constructor called"
		<< RESET << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other)
{
	std::cout << BRIGHT_YELLOW << "[Cat] Copy constructor called"
		<< RESET << std::endl;
}

Cat::~Cat(void)
{
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
	}
	return (*this);
}

void Cat::makeSound(void) const
{
	std::cout << BRIGHT_YELLOW << "* Meow! Meow! *"
		<< RESET << std::endl;
}
