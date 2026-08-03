#ifndef AFORM_HPP
# define AFORM_HPP

# include <exception>
# include <iostream>
# include <string>

class	Bureaucrat;

class AForm
{
  private:
	std::string m_name;
	bool m_isSigned;
	int m_gradeToSign;
	int m_gradeToExecute;
	std::string m_target;

	void validateGrade(int grade) const;

  protected:
	virtual void executeAction(void) const = 0;

  public:
	AForm(void);
	AForm(const AForm &other);
	AForm &operator=(const AForm &other);
	virtual ~AForm(void);

	AForm(const std::string &name, const std::string &target, int gradeToSign,
		int gradeToExecute);

	const std::string &getName(void) const;
	const std::string &getTarget(void) const;
	bool isSigned(void) const;
	int getGradeToSign(void) const;
	int getGradeToExecute(void) const;

	void beSigned(const Bureaucrat &bureaucrat);
	void execute(const Bureaucrat &executor) const;

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

	class FormNotSignedException : public std::exception
	{
		public:
		virtual const char *what(void) const throw();
	};

	static const int HIGHEST_GRADE = 1;
	static const int LOWEST_GRADE = 150;
};

std::ostream &operator<<(std::ostream &stream, const AForm &form);

#endif
