#include "Colors.hpp"
#include "WrongCat.hpp"

WrongCat::WrongCat(void) : WrongAnimal()
{
	this->m_type = "WrongCat";
	std::cout << BRIGHT_MAGENTA << "[WrongCat] Default constructor called"
		<< RESET << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal(other)
{
	std::cout << BRIGHT_MAGENTA << "[WrongCat] Copy constructor called"
		<< RESET << std::endl;
}

WrongCat::~WrongCat(void)
{
	std::cout << BRIGHT_MAGENTA << "[WrongCat] Destructor called"
		<< RESET << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &other)
{
	std::cout << BRIGHT_MAGENTA << "[WrongCat] Assignment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		WrongAnimal::operator=(other);
	}
	return (*this);
}

void WrongCat::makeSound(void) const
{
	std::cout << BRIGHT_MAGENTA << "* Meow! Meow! *"
		<< RESET << std::endl;
}
