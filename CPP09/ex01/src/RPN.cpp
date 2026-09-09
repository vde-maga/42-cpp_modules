#include "../include/RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const std::string &input) : input_(input)
{
}

RPN::RPN(const RPN &other) : input_(other.input_), stack_(other.stack_)
{
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		this->input_ = other.input_;
		this->stack_ = other.stack_;
	}
	return (*this);
}

RPN::~RPN()
{
}

void RPN::run()
{
	evaluate();
	if (this->stack_.size() != 1)
	{
		throw RPNException();
	}
	std::cout << this->stack_.top() << std::endl;
}

void RPN::evaluate()
{
	char	c;
	int		b;
	int		a;

	for (size_t i = 0; i < this->input_.size(); ++i)
	{
		c = this->input_[i];
		if (std::isspace(static_cast<unsigned char>(c)))
		{
			continue ;
		}
		if (isDigit(c))
		{
			this->stack_.push(c - '0');
		}
		else if (isOperator(c))
		{
			if (this->stack_.size() < 2)
			{
				throw RPNException();
			}
			b = this->stack_.top();
			this->stack_.pop();
			a = this->stack_.top();
			this->stack_.pop();
			if (c == '+')
			{
				this->stack_.push(a + b);
			}
			else if (c == '-')
			{
				this->stack_.push(a - b);
			}
			else if (c == '*')
			{
				this->stack_.push(a * b);
			}
			else if (c == '/')
			{
				if (b == 0)
				{
					throw RPNException();
				}
				this->stack_.push(a / b);
			}
		}
		else
		{
			throw RPNException();
		}
	}
}

bool RPN::isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

const char *RPN::RPNException::what() const throw()
{
	return ("Error");
}
