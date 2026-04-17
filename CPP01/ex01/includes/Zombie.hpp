#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>

class Zombie
{
	private:
		std::string	name;
	public:
		~Zombie(void);
		void	setName(std::string name);
		const std::string&	getName(void) const;
		void	announce( void );
};



#endif
