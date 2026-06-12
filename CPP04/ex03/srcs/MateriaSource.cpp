#include "MateriaSource.hpp"
#include "Colors.hpp"

MateriaSource::MateriaSource(void)
{
    for (int i = 0; i < 4; ++i)
        this->templates[i] = NULL;
    std::cout << BRIGHT_MAGENTA << "[MateriaSource] Default constructor called" << RESET << std::endl;
}

// Deep Copy
MateriaSource::MateriaSource(const MateriaSource &other)
{
    for (int i = 0; i < 4; ++i)
    {
        if (other.templates[i])
            this->templates[i] = other.templates[i]->clone();
        else
            this->templates[i] = NULL;
    }
    std::cout << BRIGHT_MAGENTA << "[MateriaSource] Copy constructor called" << RESET << std::endl;
}

MateriaSource::~MateriaSource(void)
{
    for (int i = 0; i < 4; ++i)
        delete this->templates[i]; // RAII
    std::cout << BRIGHT_MAGENTA << "[MateriaSource] Destructor called" << RESET << std::endl;
}

MateriaSource &MateriaSource::operator=(const MateriaSource &other)
{
    std::cout << BRIGHT_MAGENTA << "[MateriaSource] Assignment operator called" << RESET << std::endl;
    if (this != &other)
    {
        for (int i = 0; i < 4; ++i)
        {
            delete this->templates[i];
            if (other.templates[i])
                this->templates[i] = other.templates[i]->clone();
            else
                this->templates[i] = NULL;
        }
    }
    return (*this);
}

// O enunciado diz "Copies the Materia passed as a parameter". Tem de ser Deep Copy!
void MateriaSource::learnMateria(AMateria *m)
{
    if (!m)
        return;
    for (int i = 0; i < 4; ++i)
    {
        if (this->templates[i] == NULL)
        {
            this->templates[i] = m->clone(); // CLONE PARA EVITAR ALIASING/LEAKS
            delete m; // Podemos apagar o original pq já copiamos
            return;
        }
    }
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
    for (int i = 0; i < 4; ++i)
    {
        if (this->templates[i] && this->templates[i]->getType() == type)
            return (this->templates[i]->clone()); // Retorna uma cópia profunda
    }
    return (0); // Desconhecido
}