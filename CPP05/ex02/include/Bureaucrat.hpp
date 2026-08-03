#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <exception>
# include <iostream>
# include <string>

class	AForm;

class Bureaucrat
{
  private:
	std::string m_name;
	int m_grade;

  public:
	Bureaucrat(void);
	Bureaucrat(const Bureaucrat &to_copy);
	Bureaucrat &operator=(const Bureaucrat &original);
	~Bureaucrat(void);

	Bureaucrat(const std::string &name, int grade);

	const std::string &getName(void) const;
	int getGrade(void) const;

	void incrementGrade(void);
	void decrementGrade(void);

	void signForm(AForm &form) const;
	void executeForm(const AForm &form) const;

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
