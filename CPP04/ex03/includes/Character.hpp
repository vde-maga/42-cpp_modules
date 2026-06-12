#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "ICharacter.hpp"
# include "AMateria.hpp"

class Character : public ICharacter
{
  private:
    std::string m_name;
    AMateria *m_inventory[4];
    AMateria *m_floor[10];
    int m_floorCount;

  public:
    Character(void);
    Character(std::string const &name);
    Character(const Character &other);
    ~Character(void);
    Character &operator=(const Character &other);

    std::string const &getName(void) const;
    void equip(AMateria *m);
    void unequip(int idx);
    void use(int idx, ICharacter &target);
};

#endif