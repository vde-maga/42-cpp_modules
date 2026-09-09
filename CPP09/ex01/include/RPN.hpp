#ifndef RPN_HPP
# define RPN_HPP

# include <cctype>
# include <exception>
# include <iostream>
# include <stack>
# include <string>

class RPN
{
  private:
	std::string input_;
	std::stack<int> stack_;

	void evaluate();
	static bool isOperator(char c);
	static bool isDigit(char c);

	RPN();

  public:
	explicit RPN(const std::string &input);
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

	void run();

	class RPNException : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};
};

#endif
