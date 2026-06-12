#include "Ice.hpp"
#include "ICharacter.hpp"
#include "Colors.hpp"

Ice::Ice(void) : AMateria("ice")
{
    std::cout << BRIGHT_BLUE << "[Ice] Default constructor called" << RESET << std::endl;
}

Ice::Ice(const Ice &other) : AMateria(other)
{
    std::cout << BRIGHT_BLUE << "[Ice] Copy constructor called" << RESET << std::endl;
}

Ice::~Ice(void)
{
    std::cout << BRIGHT_BLUE << "[Ice] Destructor called" << RESET << std::endl;
}

Ice &Ice::operator=(const Ice &other)
{
    std::cout << BRIGHT_BLUE << "[Ice] Assignment operator called" << RESET << std::endl;
    AMateria::operator=(other);
    return (*this);
}

Ice *Ice::clone(void) const
{
    return (new Ice(*this)); // Deep copy
}

void Ice::use(ICharacter &target)
{
    std::cout << BRIGHT_BLUE << "* shoots an ice bolt at " << target.getName() << " *" << RESET << std::endl;
}