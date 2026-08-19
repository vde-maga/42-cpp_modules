#include "../include/Identifier.hpp"
#include "../include/Colors.hpp"
#include <iostream>
#include <cstdlib>

Base*	generate(void)
{
	int	random = std::rand() % 3;

	if (random == 0)
		return (new A());
	else if (random == 1)
		return (new B());
	else
		return (new C());
}

void	identify(Base* p)
{
	if (p == NULL)
	{
		std::cout << BRIGHT_RED << "Null pointer provided"
			<< RESET << std::endl;
		return;
	}

	if (dynamic_cast<A*>(p))
		std::cout << GREEN << "A"
			<< RESET << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << GREEN << "B"
			<< RESET << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << GREEN << "C"
			<< RESET << std::endl;
	else
		std::cout << BRIGHT_RED << "Unkwon Type"
			<< RESET << std::endl;
}

void	identify(Base& p)
{
	try
	{
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << GREEN << "A"
			<< RESET << std::endl;
		return;
	} catch (...) {}
	try
	{
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << GREEN << "B"
			<< RESET << std::endl;
		return;
	} catch (...) {}
	try
	{
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << GREEN << "C"
			<< RESET << std::endl;
		return;
	} catch (...) {}

	std::cout << BRIGHT_RED << "Unkwon Type" << RESET << std::endl;
}
