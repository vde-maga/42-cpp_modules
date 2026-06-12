#include "Bureaucrat.hpp"

const int Bureaucrat::HIGHEST_GRADE;
const int Bureaucrat::LOWEST_GRADE;

/* Orthodox Canonical Form */
Bureaucrat::Bureaucrat(void) :
	m_name("Default"), m_grade(LOWEST_GRADE)
{
	std::cout << BRIGHT_CYAN << "[Bureaucrat] Default constructor called for " << m_name
		<< RESET << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) :
	m_name(other.m_name), m_grade(other.m_grade)
{
	std::cout << BRIGHT_CYAN << "[Bureaucrat] Copy constructor called for " << m_name
		<< RESET << std::endl;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &original)
{
	std::cout << BRIGHT_CYAN << "[Bureaucrat] Assignment operator called for " << m_name
		<< RESET << std::endl;

	if (this != &original)
	{
		const_cast<std::string &>(this->m_name) = original.m_name;
		this->m_grade = original.m_grade;
	}
	return (*this);
}

Bureaucrat::~Bureaucrat(void)
{
	std::cout << BRIGHT_RED << "[Bureaucrat] Destructor called for " << m_name
		<< RESET << std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) :
	m_name(name), m_grade(grade)
{
	if (this->m_grade < HIGHEST_GRADE)
	{
		throw Bureaucrat::GradeTooHighException();
	}
	else if (this->m_grade > LOWEST_GRADE)
	{
		throw Bureaucrat::GradeTooLowException();
	}

	std::cout << BRIGHT_CYAN << "[Bureaucrat] Parameterized constructor called for " << m_name
		<< RESET << std::endl;
}

const std::string &Bureaucrat::getName(void) const
{
	return (this->m_name);
}

int Bureaucrat::getGrade(void) const
{
	return (this->m_grade);
}

void Bureaucrat::incrementGrade(void)
{
	if (this->m_grade <= HIGHEST_GRADE)
	{
		throw Bureaucrat::GradeTooHighException();
	}
	--this->m_grade;
}

void Bureaucrat::decrementGrade(void)
{
	if (this->m_grade >= LOWEST_GRADE)
	{
		throw Bureaucrat::GradeTooLowException();
	}
	++this->m_grade;
}

const char *Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return ("Bureaucrat exception: grade too high!");
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return ("Bureaucrat exception: grade too low!");
}

std::ostream &operator<<(std::ostream &stream, const Bureaucrat &b)
{
	stream << b.getName() << ", bureaucrat grade " << b.getGrade();
	return (stream);
}
