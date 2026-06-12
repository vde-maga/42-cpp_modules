#include "Cure.hpp"
#include "ICharacter.hpp"
#include "Colors.hpp"

Cure::Cure(void) : AMateria("cure")
{
    std::cout << BRIGHT_BLUE << "[Cure] Default constructor called" << RESET << std::endl;
}

Cure::Cure(const Cure &other) : AMateria(other)
{
    std::cout << BRIGHT_BLUE << "[Cure] Copy constructor called" << RESET << std::endl;
}

Cure::~Cure(void)
{
    std::cout << BRIGHT_BLUE << "[Cure] Destructor called" << RESET << std::endl;
}

Cure &Cure::operator=(const Cure &other)
{
    std::cout << BRIGHT_BLUE << "[Cure] Assignment operator called" << RESET << std::endl;
    AMateria::operator=(other);
    return (*this);
}

Cure *Cure::clone(void) const
{
    return (new Cure(*this));
}

void Cure::use(ICharacter &target)
{
    std::cout << BRIGHT_GREEN << "* heals " << target.getName() << "’s wounds *"<< RESET << std::endl;
}