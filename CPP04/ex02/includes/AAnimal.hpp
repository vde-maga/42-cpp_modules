#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <iostream>
# include <string>

class AAnimal
{
  protected:
	std::string m_type;

  public:
	AAnimal(void);
	AAnimal(const AAnimal &other);
	virtual ~AAnimal(void);
	AAnimal &operator=(const AAnimal &other);

	virtual void makeSound(void) const = 0;
	const std::string &getType(void) const;
};

#endif
