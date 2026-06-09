#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>
# include <string>

class WrongAnimal
{
  protected:
	std::string m_type;

  public:
	WrongAnimal(void);
	WrongAnimal(const WrongAnimal &other);
	virtual ~WrongAnimal(void);
	WrongAnimal &operator=(const WrongAnimal &other);

	void makeSound(void) const;
	const std::string &getType(void) const;
};

#endif