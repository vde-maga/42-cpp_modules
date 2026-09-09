#include "BitcoinExchange.hpp"
#include <iostream>

int	main(int argc, char **argv)
{
		BitcoinExchange btc;

	if (argc != 2)
	{
		std::cerr << "Usage: ./btc input.txt" << std::endl;
		return (1);
	}
	try
	{
		btc.execute(argv[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
