#ifndef INTERN_HPP
# define INTERN_HPP

# include <string>

class	AForm;

class Intern
{
  private:
	static AForm *createShrubberyCreationForm(const std::string &target);
	static AForm *createRobotomyRequestForm(const std::string &target);
	static AForm *createPresidentialPardonForm(const std::string &target);

  public:
	Intern(void);
	Intern(const Intern &other);
	Intern &operator=(const Intern &other);
	~Intern(void);

	AForm *makeForm(const std::string &formName,
		const std::string &target) const;
};

#endif
