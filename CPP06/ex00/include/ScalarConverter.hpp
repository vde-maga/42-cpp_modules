#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>

class ScalarConverter
{
  private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter &);
	ScalarConverter &operator=(const ScalarConverter &);
	~ScalarConverter();

	enum	LiteralType
	{
		CHAR,
		INT,
		FLOAT,
		DOUBLE,
		PSEUDO,
		INVALID
	};

	static LiteralType detectType(const std::string &str);
	static void fromChar(const std::string &str);
	static void fromInt(const std::string &str);
	static void fromFloat(const std::string &str);
	static void fromDouble(const std::string &str);
	static void fromPseudo(const std::string &str);
	static void printAll(double d);
	static bool isDigit(char c);

  public:
	static void convert(const std::string &literal);
};

#endif
