#include "Harl.hpp"
#include "Colors.hpp"
#include <iostream>

Harl::Harl(void)
{
}

Harl::Harl(const Harl &src)
{
	(void)src;
}

Harl &Harl::operator=(const Harl &rhs)
{
	(void)rhs;
	return (*this);
}

Harl::~Harl(void)
{
}

void Harl::debug(void) const
{
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info(void) const
{
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void) const
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month." << std::endl;
}

void Harl::error(void) const
{
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(const std::string &level) const
{
	static const std::size_t num_levels = 4;

	const ComplainLevel levels[num_levels] = {{"DEBUG", &Harl::debug}, {"INFO",
		&Harl::info}, {"WARNING", &Harl::warning}, {"ERROR", &Harl::error}};

	for (std::size_t i = 0; i < num_levels; ++i)
	{
		if (level == levels[i].name)
		{
			(this->*levels[i].func)();
			return ;
		}
	}

	std::cerr << RED << "Error: Invalid complaint level: \"" << level << "\"" << RESET << std::endl;
}
