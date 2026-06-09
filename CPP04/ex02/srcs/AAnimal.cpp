#include "AAnimal.hpp"
#include "Colors.hpp"

AAnimal::AAnimal(void) : type("AAnimal")
{
	std::cout << BRIGHT_CYAN << "[AAnimal] Default constructor called"
		<< RESET << std::endl;
}

AAnimal::AAnimal(const AAnimal &other) : type(other.type)
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
		this->type = other.type;
	}
	return (*this);
}

const std::string &AAnimal::getType(void) const
{
	return (this->type);
}
