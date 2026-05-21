#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie
{
  private:
	std::string _name;

  public:
	Zombie(void);
	Zombie(const std::string &name);
	~Zombie(void);

	const std::string &getName(void) const;
	void announce(void) const;
};

Zombie	*newZombie(std::string name);
void	randomChump(std::string name);

#endif
