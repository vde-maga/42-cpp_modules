#include "BitcoinExchange.hpp"

const char *BitcoinExchange::DatabaseError::what() const throw()
{
	return ("Error: could not open database.");
}

const char *BitcoinExchange::FileError::what() const throw()
{
	return ("Error: could not open file.");
}

BitcoinExchange::BitcoinExchange()
{
	loadDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : database_(other.database_)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->database_ = other.database_;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase()
{
	bool	isFirstLine;
	size_t	commaPos;
	float	rate;

	std::ifstream db("data.csv");
	if (!db.is_open())
		throw DatabaseError();
	std::string line;
	isFirstLine = true;
	while (std::getline(db, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			if (line == "date,exchange_rate")
				continue ;
		}
		commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue ;
		std::string date = line.substr(0, commaPos);
		std::string valStr = line.substr(commaPos + 1);
		rate = 0.0f;
		if (parseValue(valStr, rate))
		{
			this->database_.insert(std::make_pair(date, rate));
		}
	}
	if (this->database_.empty())
		throw DatabaseError();
}

void BitcoinExchange::execute(const std::string &inputFile) const
{
	std::ifstream input(inputFile.c_str());
	if (!input.is_open())
		throw FileError();

	std::string line;
	bool isFirstLine = true;

	while (std::getline(input, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			if (line == "date | value")
				continue ;
		}

		size_t pipePos = line.find(" | ");
		if (pipePos == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}

		std::string date = line.substr(0, pipePos);
		std::string valStr = line.substr(pipePos + 3);

		if (!isValidDate(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue ;
		}

		float value = 0.0f;
		if (!parseValue(valStr, value))
		{
			std::cout << "Error: bad input => " << valStr << std::endl;
			continue ;
		}

		if (value < 0.0f)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue ;
		}
		if (value > 1000.0f)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue ;
		}

		float rate = findClosestRate(date);
		std::cout << date << " => " << valStr << " = " << rate
			* value << std::endl;
	}
}

float BitcoinExchange::findClosestRate(const std::string &date) const
{
	std::map<std::string,
		float>::const_iterator it = this->database_.upper_bound(date);
	if (it == this->database_.begin())
	{
		return (it->second);
	}
	--it;
	return (it->second);
}

bool BitcoinExchange::isValidDate(const std::string &dateStr)
{
	int		year;
	int		month;
	int		day;
	int		daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool	isLeap;

	if (dateStr.length() != 10)
		return (false);
	if (dateStr[4] != '-' || dateStr[7] != '-')
		return (false);
	for (size_t i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7)
			continue ;
		if (!std::isdigit(static_cast<unsigned char>(dateStr[i])))
			return (false);
	}
	year = std::atoi(dateStr.substr(0, 4).c_str());
	month = std::atoi(dateStr.substr(5, 2).c_str());
	day = std::atoi(dateStr.substr(8, 2).c_str());
	if (month < 1 || month > 12)
		return (false);
	if (day < 1)
		return (false);
	if (month == 2)
	{
		isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (isLeap)
			daysInMonth[1] = 29;
	}
	return (day <= daysInMonth[month - 1]);
}

bool BitcoinExchange::parseValue(const std::string &valStr, float &value)
{
	char	c;

	if (valStr.empty())
		return (false);
	std::istringstream iss(valStr);
	iss >> value;
	if (iss.fail())
		return (false);
	while (iss.get(c))
	{
		if (!std::isspace(static_cast<unsigned char>(c)))
			return (false);
	}
	return (true);
}
