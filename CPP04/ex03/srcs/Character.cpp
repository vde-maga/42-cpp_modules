#include "Character.hpp"
#include "Colors.hpp"

Character::Character(void) : m_name("Default"), m_floorCount(0)
{
    for (int i = 0; i < 4; ++i)
        this->m_inventory[i] = NULL;
    for (int i = 0; i < 10; ++i)
        this->m_floor[i] = NULL;
    std::cout << BRIGHT_YELLOW << "[Character] Default constructor called" << RESET << std::endl;
}

Character::Character(std::string const &name) : m_name(name), m_floorCount(0)
{
    for (int i = 0; i < 4; ++i)
        this->m_inventory[i] = NULL;
    for (int i = 0; i < 10; ++i)
        this->m_floor[i] = NULL;
    std::cout << BRIGHT_YELLOW << "[Character] Parameterized constructor called" << RESET << std::endl;
}

// DEEP COPY
Character::Character(const Character &other) : ICharacter(), m_name(other.m_name), m_floorCount(0)
{
    for (int i = 0; i < 4; ++i)
    {
        if (other.m_inventory[i])
            this->m_inventory[i] = other.m_inventory[i]->clone(); // Deep copy com clone!
        else
            this->m_inventory[i] = NULL;
    }
    for (int i = 0; i < 10; ++i)
        this->m_floor[i] = NULL;
    std::cout << BRIGHT_YELLOW << "[Character] Copy constructor called" << RESET << std::endl;
}

Character::~Character(void)
{
    for (int i = 0; i < 4; ++i)
        delete this->m_inventory[i]; // RAII
    for (int i = 0; i < 10; ++i)
        delete this->m_floor[i]; // Limpa o chão (se houver)
    std::cout << BRIGHT_YELLOW << "[Character] Destructor called" << RESET << std::endl;
}

Character &Character::operator=(const Character &other)
{
    std::cout << BRIGHT_YELLOW << "[Character] Assignment operator called" << RESET << std::endl;
    if (this != &other)
    {
        this->m_name = other.m_name;
        // Limpar o inventário antigo ANTES de copiar (Regra do enunciado)
        for (int i = 0; i < 4; ++i)
        {
            delete this->m_inventory[i];
            this->m_inventory[i] = NULL;
        }
        // Deep copy
        for (int i = 0; i < 4; ++i)
        {
            if (other.m_inventory[i])
                this->m_inventory[i] = other.m_inventory[i]->clone();
        }
    }
    return (*this);
}

std::string const &Character::getName(void) const { return (this->m_name); }

void Character::equip(AMateria *m)
{
    if (!m)
        return;
    for (int i = 0; i < 4; ++i)
    {
        if (this->m_inventory[i] == NULL)
        {
            this->m_inventory[i] = m;
            return;
        }
    }
    // Inventário cheio? O enunciado diz "nothing should happen", mas não podemos fazer leak do 'm' se nos foi dado!
    // Se o Character não o equipa, tem de o deitar ao chão.
    if (m_floorCount < 10)
        this->m_floor[m_floorCount++] = m;
}

void Character::unequip(int idx)
{
    if (idx < 0 || idx >= 4 || !this->m_inventory[idx])
        return;
    // Coloca no chão em vez de dar delete (Regra do enunciado)
    if (m_floorCount < 10)
        this->m_floor[m_floorCount++] = this->m_inventory[idx];
    this->m_inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter &target)
{
    if (idx >= 0 && idx < 4 && this->m_inventory[idx])
        this->m_inventory[idx]->use(target);
}