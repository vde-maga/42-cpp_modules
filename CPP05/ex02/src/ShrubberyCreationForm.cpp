#include "../include/Colors.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(void) :
	AForm("ShrubberyCreationForm", "Default", 145, 137)
{
	std::cout << BRIGHT_CYAN << "[ShrubberyCreationForm] Default constructor called"
		<< RESET << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) :
	AForm(other)
{
	std::cout << BRIGHT_CYAN << "[ShrubberyCreationForm] Copy constructor called"
		<< RESET << std::endl;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	std::cout << BRIGHT_CYAN << "[ShrubberyCreationForm] Assignment operator called"
		<< RESET << std::endl;

	if (this != &other)
	{
		AForm::operator=(other);
	}
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	std::cout << BRIGHT_RED << "[ShrubberyCreationForm] Destructor called"
		<< RESET << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) :
	AForm("ShrubberyCreationForm", target, 145, 137)
{
	std::cout << BRIGHT_CYAN << "[ShrubberyCreationForm] Parameterized constructor called for target: "
		<< target << RESET << std::endl;
}

void ShrubberyCreationForm::executeAction(void) const
{
	std::string filename = this->getTarget() + "_shrubbery";
	std::ofstream outfile(filename.c_str());

	if (!outfile.is_open())
	{
		std::cerr << RED << "Error: Could not create file "
			<< filename << RESET << std::endl;
		return ;
	}

	outfile << "       /\\       " << std::endl;
	outfile << "      /  \\      " << std::endl;
	outfile << "     /    \\     " << std::endl;
	outfile << "    /      \\    " << std::endl;
	outfile << "   /        \\   " << std::endl;
	outfile << "  /__________\\  " << std::endl;
	outfile << "       ||       " << std::endl;
	outfile << "       ||       " << std::endl;

	outfile.close();
	std::cout << GREEN << "Shrubbery planted at "
		<< filename << RESET << std::endl;
}
