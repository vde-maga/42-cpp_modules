#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

# include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
  public:
	WrongCat(void);
	WrongCat(const WrongCat &other);
	~WrongCat(void);
	WrongCat &operator=(const WrongCat &other);

	virtual void makeSound(void) const;
};

#endif
