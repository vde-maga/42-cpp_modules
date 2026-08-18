#include "../include/Bureaucrat.hpp"
#include "../include/Colors.hpp"
#include "../include/Form.hpp"

const int Form::HIGHEST_GRADE;
const int Form::LOWEST_GRADE;

/* Orthodox Canonical Form */
Form::Form(void) :
	m_name("Default"), m_isSigned(false), m_gradeToSign(LOWEST_GRADE),
	m_gradeToExecute(LOWEST_GRADE)
{
	std::cout << BRIGHT_CYAN << "[Form] Default constructor called for "
		<< m_name << RESET << std::endl;
}

Form::Form(const Form &other) :
	m_name(other.m_name), m_isSigned(other.m_isSigned),
	m_gradeToSign(other.m_gradeToSign), m_gradeToExecute(other.m_gradeToExecute)
{
	std::cout << BRIGHT_CYAN << "[Form] Copy constructor called for "
		<< m_name << RESET << std::endl;
}

Form &Form::operator=(const Form &original)
{
	std::cout << BRIGHT_CYAN << "[Form] Assignment operator called for "
		<< m_name << RESET << std::endl;

	if (this != &original)
	{
		this->m_name = original.m_name;
		this->m_isSigned = original.m_isSigned;
		this->m_gradeToSign = original.m_gradeToSign;
		this->m_gradeToExecute = original.m_gradeToExecute;
	}
	return (*this);
}

Form::~Form(void)
{
	std::cout << BRIGHT_RED << "[Form] Destructor called for "
		<< m_name << RESET << std::endl;
}

/* Parameterized Consructor*/
Form::Form(const std::string &name, int gradeToSign, int gradeToExecute):
	m_name(name), m_isSigned(false), m_gradeToSign(gradeToSign),
	m_gradeToExecute(gradeToExecute)
{
	validateGrade(gradeToSign);
	validateGrade(gradeToExecute);
	
	std::cout << BRIGHT_CYAN << "[Form] Parameterized constructor called for "
		<< m_name << RESET << std::endl;
}

/* Getters */
const std::string &Form::getName(void) const
{
	return (this->m_name);
}

bool Form::isSigned(void) const
{
	return (this->m_isSigned);
}

int Form::getGradeToSign(void) const
{
	return (this->m_gradeToSign);
}

int Form::getGradeToExecute(void) const
{
	return (this->m_gradeToExecute);
}

/* Modifiers */
void Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > this->m_gradeToSign)
	{
		throw Form::GradeTooLowException();
	}
	this->m_isSigned = true;
}

void Form::validateGrade(int grade) const
{
	if (grade < HIGHEST_GRADE)
	{
		throw Form::GradeTooHighException();
	}
	else if (grade > LOWEST_GRADE)
	{
		throw Form::GradeTooLowException();
	}
}

/* Exceptions */
const char *Form::GradeTooHighException::what(void) const throw()
{
	return ("Form exception: grade too high!");
}

const char *Form::GradeTooLowException::what(void) const throw()
{
	return ("Form exception: grade too low!");
}

std::ostream &operator<<(std::ostream &stream, const Form &form)
{
	stream << "Form " << form.getName()
		<< " [signed: " << (form.isSigned() ? "yes" : "no")
		<< ", grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute()
		<< "]";
	return (stream);
}
