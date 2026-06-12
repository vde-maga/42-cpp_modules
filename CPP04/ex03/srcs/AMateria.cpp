#include "AMateria.hpp"
#include "ICharacter.hpp"
#include "Colors.hpp"

AMateria::AMateria(void) : m_type("undefined")
{
    std::cout << BRIGHT_CYAN << "[AMateria] Default constructor called" << RESET << std::endl;
}

AMateria::AMateria(std::string const &type) : m_type(type)
{
    std::cout << BRIGHT_CYAN << "[AMateria] Parameterized constructor called" << RESET << std::endl;
}

AMateria::AMateria(const AMateria &other) : m_type(other.m_type)
{
    std::cout << BRIGHT_CYAN << "[AMateria] Copy constructor called" << RESET << std::endl;
}

AMateria::~AMateria(void)
{
    std::cout << BRIGHT_CYAN << "[AMateria] Destructor called" << RESET << std::endl;
}

// "While assigning a Materia to another, copying the type doesn’t make sense."
AMateria &AMateria::operator=(const AMateria &other)
{
    std::cout << BRIGHT_CYAN << "[AMateria] Assignment operator called (type NOT copied)" << RESET << std::endl;
    (void)other; // Defensivo: Ignoramos intencionalmente o other.type
    return (*this);
}

std::string const &AMateria::getType(void) const { return (this->m_type); }

void AMateria::use(ICharacter &target)
{
    std::cout << BRIGHT_CYAN << "* uses undefined materia on " << target.getName() << " *" << RESET << std::endl;
}