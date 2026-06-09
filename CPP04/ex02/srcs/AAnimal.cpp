#include "AAnimal.hpp"
#include "Colors.hpp"

AAnimal::AAnimal(void) : m_type("AAnimal")
{
	std::cout << BRIGHT_CYAN << "[AAnimal] Default constructor called"
		<< RESET << std::endl;
}

AAnimal::AAnimal(const AAnimal &other) : m_type(other.m_type)
{
	std::cout << BRIGHT_CYAN << "[AAnimal] Copy constructor called"
		<< RESET << std::endl;
}

AAnimal::~AAnimal(void)
{
	std::cout << BRIGHT_CYAN << "[AAnimal] Destructor called"
		<< RESET << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &other)
{
	std::cout << BRIGHT_CYAN << "[AAnimal] Assignment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		this->m_type = other.m_type;
	}
	return (*this);
}

const std::string &AAnimal::getType(void) const
{
	return (this->m_type);
}
