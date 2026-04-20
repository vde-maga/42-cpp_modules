#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"
#include <iostream>

void subject_test(void) 
{
    {
        Weapon club = Weapon("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club");
        bob.attack();
    }
    {
        Weapon club = Weapon("crude spiked club");
        HumanB jim("Jim");
        jim.setWeapon(club);
        jim.attack();
        club.setType("some other type of club");
        jim.attack();
    }
}

void defensive_test(void) 
{
	std::cout << "\n--- Defensive Tests ---" << std::endl;

	// Teste: HumanB sem arma (previne UB de dereferenciar NULL)
	HumanB arthur("Arthur");
	arthur.attack(); // Deve imprimir que não tem arma, sem crashar (Segmentation Fault)
}

int	main(void) 
{
	std::cout << "\n--- Subject Tests ---" << std::endl;
	subject_test();
	defensive_test();
    return (0);
}
