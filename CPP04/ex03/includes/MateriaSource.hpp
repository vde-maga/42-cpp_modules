#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"
# include "AMateria.hpp"

class MateriaSource : public IMateriaSource
{
  private:
    AMateria *templates[4];

  public:
    MateriaSource(void);
    MateriaSource(const MateriaSource &other);
    ~MateriaSource(void);
    MateriaSource &operator=(const MateriaSource &other);

    void learnMateria(AMateria *m);
    AMateria *createMateria(std::string const &type);
};

#endif