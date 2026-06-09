#include "Brain.hpp"
#include "Colors.hpp"
#include <iostream>

Brain::Brain(void)
{
	std::cout << BRIGHT_CYAN << "[Brain] Default constructor called"
		<< RESET << std::endl;
}

Brain::Brain(const Brain &other)
{
	*this = other;
	std::cout << BRIGHT_CYAN << "[Brain] Copy constructor called"
		<< RESET << std::endl;
}

Brain &Brain::operator=(const Brain &other)
{
	std::cout << BRIGHT_CYAN << "[Brain] Assignment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		for (int i = 0; i < 100; ++i)
			this->ideas[i] = other.ideas[i];
	}
	return (*this);
}

Brain::~Brain(void)
{
	std::cout << BRIGHT_CYAN << "[Brain] Destructor called"
		<< RESET << std::endl;
}

const std::string &Brain::getIdea(unsigned int idx) const
{
	if (idx >= 100)
		return (this->ideas[0]);
	return (this->ideas[idx]);
}

void Brain::setIdea(unsigned int idx, const std::string &idea)
{
	if (idx < 100)
		this->ideas[idx] = idea;
}
