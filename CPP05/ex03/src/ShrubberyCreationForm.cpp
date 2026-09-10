#include "../include/Colors.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include <fstream>
#include <stdexcept>

ShrubberyCreationForm::ShrubberyCreationForm(void) : AForm("ShrubberyCreationForm",
	"Default", 145, 137)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other)
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
		AForm::operator=(other);
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("ShrubberyCreationForm",
	target, 145, 137)
{
}

void ShrubberyCreationForm::executeAction(void) const
{
	std::string filename = this->getTarget() + "_shrubbery";
	std::ofstream outfile(filename.c_str());

	if (!outfile.is_open())
		throw std::runtime_error("Error: Could not create file " + filename);

	outfile << "       /\\       " << std::endl;
	outfile << "      /  \\      " << std::endl;
	outfile << "     /    \\     " << std::endl;
	outfile << "    /      \\    " << std::endl;
	outfile << "   /        \\   " << std::endl;
	outfile << "  /__________\\  " << std::endl;
	outfile << "       ||       " << std::endl;
	outfile << "       ||       " << std::endl;

	outfile.close();
	std::cout << "Shrubbery planted at " << filename << std::endl;
}