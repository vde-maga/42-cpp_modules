#include "Animal.hpp"
#include "Colors.hpp"

Animal::Animal(void) : type("Animal")
{
	std::cout << BRIGHT_CYAN << "[Animal] Default constructor called"
		<< RESET << std::endl;
}

Animal::Animal(const Animal &other) : type(other.type)
{
	std::cout << BRIGHT_CYAN << "[Animal] Copy constructor called"
		<< RESET << std::endl;
}

Animal::~Animal(void)
{
	std::cout << BRIGHT_CYAN << "[Animal] Destructor called"
		<< RESET << std::endl;
}

Animal &Animal::operator=(const Animal &other)
{
	std::cout << BRIGHT_CYAN << "[Animal] Assignment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		this->type = other.type;
	}
	return (*this);
}

void Animal::makeSound(void) const
{
	std::cout << BRIGHT_CYAN << "* Generic animal sound *"
		<< RESET << std::endl;
}

const std::string &Animal::getType(void) const
{
	return (this->type);
}
