#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"

class HumanA
{
  private:
	std::string _name;
	Weapon &_weapon;
		// Referência: HumanA sempre tem arma. Não pode ser reassinada.

  public:
	HumanA(const std::string &name, Weapon &weapon);

	void attack(void) const;
};

#endif
