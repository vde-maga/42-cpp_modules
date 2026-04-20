// File: main.cpp
#include "replace.hpp"
#include <iostream>

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return (1);
	}
	const std::string filename = argv[1];
	const std::string s1 = argv[2];
	const std::string s2 = argv[3];
	if (s1.empty())
	{
		std::cerr << "Error: s1 cannot be empty." << std::endl;
		return (1);
	}
	if (!replaceInFile(filename, s1, s2))
	{
		std::cerr << "Error: Failed to process file." << std::endl;
		return (1);
	}
	return (0);
}
