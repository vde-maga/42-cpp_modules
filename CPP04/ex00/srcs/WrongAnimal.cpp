#include "Colors.hpp"
#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : type("WrongAnimal")
{
	std::cout << BRIGHT_RED << "[WrongAnimal] Default constructor called"
		<< RESET << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other) : type(other.type)
{
	std::cout << BRIGHT_RED << "[WrongAnimal] Copy constructor called"
		<< RESET << std::endl;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << BRIGHT_RED << "[WrongAnimal] Destructor called"
		<< RESET << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other)
{
	std::cout << BRIGHT_RED << "[WrongAnimal] Assignment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		this->type = other.type;
	}
	return (*this);
}

void WrongAnimal::makeSound(void) const
{
	std::cout << BRIGHT_RED << "* WrongAnimal sound *"
		<< RESET << std::endl;
}

const std::string &WrongAnimal::getType(void) const
{
	return (this->type);
}
