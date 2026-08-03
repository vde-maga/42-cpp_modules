#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
  private:
	static unsigned int _seed;
	virtual void executeAction(void) const;

  public:
	RobotomyRequestForm(void);
	RobotomyRequestForm(const RobotomyRequestForm &other);
	RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
	~RobotomyRequestForm(void);

	RobotomyRequestForm(const std::string &target);
};

#endif
