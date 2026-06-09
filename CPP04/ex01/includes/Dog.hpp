#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal
{
  private:
	Brain *m_brain;

  public:
	Dog(void);
	Dog(const Dog &other);
	~Dog(void);
	Dog &operator=(const Dog &other);

	virtual void makeSound(void) const;

	Brain *getBrain(void) const;
};

#endif
