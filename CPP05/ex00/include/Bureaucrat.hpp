#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include "Colors.hpp"
# include <exception>
# include <iostream>
# include <string>

class Bureaucrat
{
  private:
	const std::string m_name;
	int m_grade;

  public:
	/* Orthodox Canonical Form */
	Bureaucrat(void);
	Bureaucrat(const Bureaucrat &to_copy);
	Bureaucrat &operator=(const Bureaucrat &original);
	~Bureaucrat(void);

	/* Parameterized Constructor */
	Bureaucrat(const std::string &name, int grade);

	/* Getters */
	const std::string &getName(void) const;
	int getGrade(void) const;

	/* Modifiers */
	void incrementGrade(void);
	void decrementGrade(void);

	/* Exceptions */
	class GradeTooHighException : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};

	class GradeTooLowException : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};

	static const int HIGHEST_GRADE = 1;
	static const int LOWEST_GRADE = 150;
};

std::ostream &operator<<(std::ostream &stream, const Bureaucrat &b);

#endif
