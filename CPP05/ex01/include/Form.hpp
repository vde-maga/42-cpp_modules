#ifndef FORM_HPP
# define FORM_HPP

# include <exception>
# include <iostream>
# include <string>

class Bureaucrat;

class Form
{
  private:
    std::string m_name;
    bool m_isSigned;
    int m_gradeToSign;
    int m_gradeToExecute;

    void validateGrade(int grade) const;

  public:
    /* Orthodox Canonical Form */
    Form(void);
    Form(const Form &to_copy);
    Form &operator=(const Form &original);
    ~Form(void);

    /* Parameterized Constructor */
    Form(const std::string &name, int gradeToSign, int gradeToExecute);

    /* Getters */
    const std::string &getName(void) const;
    bool isSigned(void) const;
    int getGradeToSign(void) const;
    int getGradeToExecute(void) const;

    /* Modifiers */
    void beSigned(const Bureaucrat &bureaucrat);

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

std::ostream &operator<<(std::ostream &stream, const Form &form);

#endif
