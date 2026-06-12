#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <iostream>
# include <string>

class ICharacter;

class AMateria
{
  protected:
    std::string m_type;

  public:
    AMateria(void);
    AMateria(std::string const &type);
    AMateria(const AMateria &other);
    virtual ~AMateria(void);
    AMateria &operator=(const AMateria &other);

    std::string const &getType(void) const;
    virtual AMateria *clone(void) const = 0;
    virtual void use(ICharacter &target);
};

#endif