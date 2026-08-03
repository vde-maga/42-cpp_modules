#include "../include/Colors.hpp"
#include "../include/PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) :
	AForm("PresidentialPardonForm", "Default", 25, 5)
{
	std::cout << BRIGHT_CYAN << "[PresidentialPardonForm] Default constructor called"
		<< RESET << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) :
	AForm(other)
{
	std::cout << BRIGHT_CYAN << "[PresidentialPardonForm] Copy constructor called"
		<< RESET << std::endl;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	std::cout << BRIGHT_CYAN << "[PresidentialPardonForm] Assignment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		AForm::operator=(other);
	}
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
	std::cout << BRIGHT_RED << "[PresidentialPardonForm] Destructor called"
		<< RESET << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) :
	AForm("PresidentialPardonForm", target, 25, 5)
{
	std::cout << BRIGHT_CYAN << "[PresidentialPardonForm] Parameterized constructor called for target: "
		<< target << RESET << std::endl;
}

void PresidentialPardonForm::executeAction(void) const
{
	std::cout << GREEN << this->getTarget() << " has been pardoned by Zaphod Beeblebrox."
		<< RESET << std::endl;
}
