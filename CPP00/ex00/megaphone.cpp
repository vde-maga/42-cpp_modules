#include <cctype>
#include <string>
#include <iostream>

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for (int i = 1; i < argc; ++i)
	{
		if (i > 1)
			std::cout << ' ';
		std::string str(argv[i]);
		for (size_t j = 0; j < str.length(); ++j)
			std::cout << static_cast<char>(std::toupper(argv[i][j]));
	}
	std::cout << std::endl;
	return (0);
}
