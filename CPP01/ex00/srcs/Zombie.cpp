#include "Zombie.hpp"

Zombie::~Zombie(void)
{

}

void	Zombie::announce( void )
{
	std::count << this->name << << "BraiiiiiiinnnzzzZ..." << std::endl;
}
