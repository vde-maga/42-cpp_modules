#include "Colors.hpp"
#include "Harl.hpp"
#include <iostream>

const Harl::ComplainLevel Harl::levels[] =
{
	{"DEBUG", &Harl::debug},
	{"INFO", &Harl::info},
	{"WARNING", &Harl::warning},
	{"ERROR", &Harl::error}
};

const int Harl::num_levels = 4;

Harl::Harl(void)
{
}

Harl::~Harl(void)
{
}

void Harl::debug(void) const
{
	std::cout << GREEN << "[DEBUG] " << RESET
		<< "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!"
		<< std::endl;
}

void Harl::info(void) const
{
	std::cout << CYAN << "[INFO] " << RESET
		<< "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!"
		<< std::endl;
}

void Harl::warning(void) const
{
	std::cout << YELLOW << "[WARNING] " << RESET
		<< "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month."
		<< std::endl;
}

void Harl::error(void) const
{
	std::cout << RED << "[ERROR] " << RESET
		<< "This is unacceptable! I want to speak to the manager now."
		<< std::endl;
}

void Harl::complain(const std::string &level) const
{
	for (int i = 0; i < num_levels; ++i)
	{
		if (level == levels[i].name)
		{
			(this->*levels[i].func)();
			return ;
		}
	}

	std::cerr << BRIGHT_RED << "[UNKNOWN] " << RESET
		<< "Harl doesn't know how to complain about: \"" << level << "\""
		<< std::endl;
}
