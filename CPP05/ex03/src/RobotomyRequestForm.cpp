#include "../include/Colors.hpp"
#include "../include/RobotomyRequestForm.hpp"

unsigned int RobotomyRequestForm::_seed = 42;

RobotomyRequestForm::RobotomyRequestForm(void) : AForm("RobotomyRequestForm",
	"Default", 72, 45)
{
	std::cout << BRIGHT_CYAN << "[RobotomyRequestForm] Default constructor called" << RESET << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other)
{
	std::cout << BRIGHT_CYAN << "[RobotomyRequestForm] Copy constructor called" << RESET << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	std::cout << BRIGHT_CYAN << "[RobotomyRequestForm] Assignment operator called" << RESET << std::endl;
	if (this != &other)
	{
		AForm::operator=(other);
	}
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
	std::cout << BRIGHT_RED << "[RobotomyRequestForm] Destructor called" << RESET << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target) : AForm("RobotomyRequestForm",
	target, 72, 45)
{
	std::cout << BRIGHT_CYAN << "[RobotomyRequestForm] Parameterized constructor called for target: " << target << RESET << std::endl;
}

void RobotomyRequestForm::executeAction(void) const
{
	_seed = (_seed * 1103515245 + 12345) & 0x7fffffff;
	bool success = (_seed % 2 == 0);

	std::cout << YELLOW << "* BZZZZZ... DRILLING NOISES... *\n" << RESET;
	if (success)
	{
		std::cout << GREEN << this->getTarget() << " has been robotomized successfully!" << RESET << std::endl;
	}
	else
	{
		std::cout << RED << "Robotomy of " << this->getTarget() << " failed." << RESET << std::endl;
	}
}
