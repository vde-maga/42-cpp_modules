#include "../include/AForm.hpp"
#include "../include/Colors.hpp"
#include "../include/Intern.hpp"
#include "../include/PresidentialPardonForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include <cstddef>
#include <iostream>

AForm *Intern::createShrubberyCreationForm(const std::string &target)
{
	return (new ShrubberyCreationForm(target));
}

AForm *Intern::createRobotomyRequestForm(const std::string &target)
{
	return (new RobotomyRequestForm(target));
}

AForm *Intern::createPresidentialPardonForm(const std::string &target)
{
	return (new PresidentialPardonForm(target));
}

Intern::Intern(void)
{
	std::cout << BRIGHT_CYAN << "[Intern] Default constructor called"
		<< RESET << std::endl;
}

Intern::Intern(const Intern &other)
{
	(void)other;
	std::cout << BRIGHT_CYAN << "[Intern] Copy constructor called"
		<< RESET << std::endl;
}

Intern &Intern::operator=(const Intern &other)
{
	(void)other;
	std::cout << BRIGHT_CYAN << "[Intern] Assignment operator called"
		<< RESET << std::endl;
	return (*this);
}

Intern::~Intern(void)
{
	std::cout << BRIGHT_RED << "[Intern] Destructor called"
		<< RESET << std::endl;
}

AForm *Intern::makeForm(const std::string &formName,
	const std::string &target) const
{
	struct			FormEntry
	{
		std::string name;
		AForm		*(*creator)(const std::string &);
	};

	const FormEntry	forms[] = {
		{"shrubbery creation", &Intern::createShrubberyCreationForm},
		{"robotomy request", &Intern::createRobotomyRequestForm},
		{"presidential pardon", &Intern::createPresidentialPardonForm}
	};

	const std::size_t num_forms = sizeof(forms) / sizeof(forms[0]);

	for (std::size_t i = 0; i < num_forms; ++i)
	{
		if (forms[i].name == formName)
		{
			std::cout << GREEN << "Intern creates " << formName
				<< RESET << std::endl;
			return (forms[i].creator(target));
		}
	}

	std::cerr << RED << "Error: Intern could not find form '" << formName
		<< "'" << RESET << std::endl;
	return (NULL);
}
