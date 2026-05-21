#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie
{
  private:
	std::string _name;

  public:
	Zombie(void);
	~Zombie(void);

	void setName(const std::string &name);
	const std::string &getName(void) const;
	void announce(void) const;
};

Zombie	*zombieHorde(int n, const std::string &name);

#endif
