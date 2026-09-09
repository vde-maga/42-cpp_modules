#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <cctype>
# include <cstdlib>
# include <exception>
# include <fstream>
# include <iostream>
# include <map>
# include <sstream>
# include <string>

class BitcoinExchange
{
  private:
	std::map<std::string, float> database_;

	void loadDatabase();
	float findClosestRate(const std::string &date) const;

	static bool isValidDate(const std::string &dateStr);
	static bool parseValue(const std::string &valStr, float &value);

  public:
	class DatabaseError : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};
	class FileError : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	virtual ~BitcoinExchange();

	void execute(const std::string &inputFile) const;
};

#endif
