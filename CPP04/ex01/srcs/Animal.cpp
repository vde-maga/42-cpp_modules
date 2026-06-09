#include "Animal.hpp"
#include "Colors.hpp"

Animal::Animal(void) : m_type("Animal")
{
	std::cout << BRIGHT_CYAN << "[Animal] Default constructor called"
		<< RESET << std::endl;
}

Animal::Animal(const Animal &other) : m_type(other.m_type)
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
		this->m_type = other.m_type;
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
	return (this->m_type);
}
