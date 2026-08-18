#include "../include/Colors.hpp"
#include "../include/ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <sstream>

ScalarConverter::ScalarConverter()
{
}
ScalarConverter::ScalarConverter(const ScalarConverter &)
{
}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &)
{
	return (*this);
}
ScalarConverter::~ScalarConverter()
{
}

bool ScalarConverter::isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

ScalarConverter::LiteralType ScalarConverter::detectType(const std::string &str)
{
	bool	hasDot;
	bool	hasF;
	size_t	i;

	if (str.empty())
		return (INVALID);
	if (str == "nan" || str == "nanf" || str == "+inf" || str == "-inf"
		|| str == "+inff" || str == "-inff")
	{
		return (PSEUDO);
	}
	hasDot = false;
	hasF = false;
	i = 0;
	if (str[0] == '+' || str[0] == '-')
	{
		i = 1;
	}
	if (i == str.length())
	{
		return (INVALID);
	}
	for (; i < str.length(); ++i)
	{
		if (str[i] == '.')
		{
			if (hasDot)
				return (INVALID);
			hasDot = true;
		}
		else if (str[i] == 'f' || str[i] == 'F')
		{
			if (hasF || i != str.length() - 1)
				return (INVALID);
			hasF = true;
		}
		else if (!isDigit(str[i]))
		{
			return (INVALID);
		}
	}
	if (hasF)
		return (FLOAT);
	if (hasDot)
		return (DOUBLE);
	if (str.length() == 1)
		return (CHAR);
	return (INT);
}

void ScalarConverter::printAll(double d)
{
	float	f;


	std::cout << BRIGHT_CYAN << "char: " << RESET;
	if (d != d ||
			d == std::numeric_limits<double>::infinity() ||
			d == -std::numeric_limits<double>::infinity() ||
			d < 0 || d > 255)
	{
		std::cout << BRIGHT_RED << "impossible" << RESET << std::endl;
	}
	else if (d < 32 || d > 126)
		std::cout << YELLOW << "Non displayable" << RESET << std::endl;
	else
		std::cout << GREEN << "'" << static_cast<char>(d) << "'" << RESET << std::endl;



	std::cout << BRIGHT_CYAN << "int: " << RESET;
	if (d != d ||
			d == std::numeric_limits<double>::infinity() ||
			d == -std::numeric_limits<double>::infinity() ||
			d < std::numeric_limits<int>::min() ||
			d > std::numeric_limits<int>::max())
	{
		std::cout << BRIGHT_RED << "impossible" << RESET << std::endl;
	}
	else
		std::cout << GREEN << static_cast<int>(d) << RESET << std::endl;



	std::cout << BRIGHT_CYAN << "float: " << RESET;
	if (d != d)
	{
		std::cout << GREEN << "nanf" << RESET << std::endl;
	}
	else if (d == std::numeric_limits<double>::infinity())
	{
		std::cout << GREEN << "inff" << RESET << std::endl;
	}
	else if (d == -std::numeric_limits<double>::infinity())
	{
		std::cout << GREEN << "-inff" << RESET << std::endl;
	}
	else if (d > std::numeric_limits<float>::max() ||
			d < -std::numeric_limits<float>::max())
	{
		std::cout << BRIGHT_RED << "impossible" << RESET << std::endl;
	}
	else
	{
		f = static_cast<float>(d);
		std::cout << GREEN;
		if (f <= 1e15 && f >= -1e15
			&& static_cast<double>(static_cast<long long>(f)) == static_cast<double>(f))
		{
			std::cout << static_cast<long long>(f) << ".0f";
		}
		else
		{
			std::cout << f << "f";
		}
		std::cout << RESET << std::endl;
	}



	std::cout << BRIGHT_CYAN << "double: " << RESET;
	if (d != d)
	{
		std::cout << GREEN << "nan" << RESET << std::endl;
	}
	else if (d == std::numeric_limits<double>::infinity())
	{
		std::cout << GREEN << "inf" << RESET << std::endl;
	}
	else if (d == -std::numeric_limits<double>::infinity())
	{
		std::cout << GREEN << "-inf" << RESET << std::endl;
	}
	else
	{
		std::cout << GREEN;
		if (d <= 1e15 && d >= -1e15
			&& static_cast<double>(static_cast<long long>(d)) == d)
		{
			std::cout << static_cast<long long>(d) << ".0";
		}
		else
		{
			std::cout << d;
		}
		std::cout << RESET << std::endl;
	}
}

void ScalarConverter::fromInt(const std::string &str)
{
	double	d;

	std::stringstream ss(str);
	ss >> d;
	if (ss.fail())
	{
		d = (str[0] == '-') ?
			-std::numeric_limits<double>::infinity() :
			std::numeric_limits<double>::infinity();
	}

	printAll(d);
}

void ScalarConverter::fromFloat(const std::string &str)
{
	double	d;

	std::string s = str;
	if (!s.empty() && (s[s.length() - 1] == 'f' || s[s.length() - 1] == 'F'))
	{
		s = s.substr(0, s.length() - 1);
	}
	std::stringstream ss(s);
	ss >> d;
	if (ss.fail())
	{
		d = (s[0] == '-') ?
			-std::numeric_limits<double>::infinity() :
			std::numeric_limits<double>::infinity();
	}

	printAll(d);
}

void ScalarConverter::fromDouble(const std::string &literal)
{
	double	d;

	std::stringstream ss(literal);
	ss >> d;
	if (ss.fail())
		d = (literal[0] == '-') ?
			-std::numeric_limits<double>::infinity() :
			std::numeric_limits<double>::infinity();

	printAll(d);
}

void ScalarConverter::fromChar(const std::string &literal)
{
	char	c;
	double	d;

	c = literal[0];
	d = static_cast<double>(c);

	printAll(d);
}

void ScalarConverter::fromPseudo(const std::string &literal)
{
	double	d;

	d = 0.0;
	if (literal == "nan" || literal == "nanf")
		d = std::numeric_limits<double>::quiet_NaN();
	else if (literal == "+inf" || literal == "+inff")
		d = std::numeric_limits<double>::infinity();
	else if (literal == "-inf" || literal == "-inff")
		d = -std::numeric_limits<double>::infinity();

	printAll(d);
}

void ScalarConverter::convert(const std::string &literal)
{
	LiteralType	type;

	if (literal.empty())
	{
		std::cerr << BRIGHT_RED << "Error: empty input"
			<< RESET << std::endl;
		return ;
	}
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
	{
		fromChar(std::string(1, literal[1]));
		return ;
	}
	type = detectType(literal);
	switch (type)
	{
	case (CHAR):
		fromChar(literal);
		break ;
	case (INT):
		fromInt(literal);
		break ;
	case (FLOAT):
		fromFloat(literal);
		break ;
	case (DOUBLE):
		fromDouble(literal);
		break ;
	case (PSEUDO):
		fromPseudo(literal);
		break ;
	default:
		std::cerr << BRIGHT_RED << "Error: Invalid Literal Format"
			<< RESET << std::endl;
		break ;
	}
}
