#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/Colors.hpp"

const int AForm::HIGHEST_GRADE;
const int AForm::LOWEST_GRADE;

AForm::AForm(void) :
	m_name("Default"), m_isSigned(false), m_gradeToSign(LOWEST_GRADE),
	m_gradeToExecute(LOWEST_GRADE), m_target("Default")
{
	std::cout << BRIGHT_CYAN << "[AForm] Default constructor called for "
		<< m_name << RESET << std::endl;
}

AForm::AForm(const AForm &other) :
	m_name(other.m_name), m_isSigned(other.m_isSigned),
	m_gradeToSign(other.m_gradeToSign), m_gradeToExecute(other.m_gradeToExecute),
	m_target(other.m_target)
{
	std::cout << BRIGHT_CYAN << "[AForm] Copy constructor called for "
		<< m_name << RESET << std::endl;
}

AForm &AForm::operator=(const AForm &other)
{
	std::cout << BRIGHT_CYAN << "[AForm] Assignment operator called for "
		<< m_name << RESET << std::endl;

	if (this != &other)
	{
		this->m_name = other.m_name;
		this->m_isSigned = other.m_isSigned;
		this->m_gradeToSign = other.m_gradeToSign;
		this->m_gradeToExecute = other.m_gradeToExecute;
		this->m_target = other.m_target;
	}
	return (*this);
}

AForm::~AForm(void)
{
	std::cout << BRIGHT_RED << "[AForm] Destructor called for "
		<< m_name << RESET << std::endl;
}

AForm::AForm(const std::string &name, const std::string &target, int gradeToSign, int gradeToExecute) :
	m_name(name), m_isSigned(false), m_gradeToSign(gradeToSign),
	m_gradeToExecute(gradeToExecute), m_target(target)
{

	validateGrade(gradeToSign);
	validateGrade(gradeToExecute);

	std::cout << BRIGHT_CYAN << "[AForm] Parameterized constructor called for "
		<< m_name << RESET << std::endl;
}

const std::string &AForm::getName(void) const
{
	return (this->m_name);
}

const std::string &AForm::getTarget(void) const
{
	return (this->m_target);
}

bool AForm::isSigned(void) const
{
	return (this->m_isSigned);
}

int AForm::getGradeToSign(void) const
{
	return (this->m_gradeToSign);
}

int AForm::getGradeToExecute(void) const
{
	return (this->m_gradeToExecute);
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > this->m_gradeToSign)
	{
		throw AForm::GradeTooLowException();
	}
	this->m_isSigned = true;
}

void AForm::execute(const Bureaucrat &executor) const
{
	if (!this->m_isSigned)
	{
		throw AForm::FormNotSignedException();
	}
	if (executor.getGrade() > this->m_gradeToExecute)
	{
		throw AForm::GradeTooLowException();
	}
	this->executeAction();
}

void AForm::validateGrade(int grade) const
{
	if (grade < HIGHEST_GRADE)
	{
		throw AForm::GradeTooHighException();
	}
	else if (grade > LOWEST_GRADE)
	{
		throw AForm::GradeTooLowException();
	}
}

const char *AForm::GradeTooHighException::what(void) const throw()
{
	return ("AForm exception: grade too high!");
}

const char *AForm::GradeTooLowException::what(void) const throw()
{
	return ("AForm exception: grade too low!");
}

const char *AForm::FormNotSignedException::what(void) const throw()
{
	return ("AForm exception: form is not signed!");
}

std::ostream &operator<<(std::ostream &stream, const AForm &form)
{
	stream << "AForm " << form.getName() << " [signed: "
		<< (form.isSigned() ? "yes" : "no") << ", grade to sign: "
		<< form.getGradeToSign() << ", grade to execute: "
		<< form.getGradeToExecute() << ", target: "
		<< form.getTarget() << "]";

	return (stream);
}
