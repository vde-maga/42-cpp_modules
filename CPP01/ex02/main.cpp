#include <iostream>

#define UNDERLINE "\033[4m"
#define RESET "\033[0m\033[24m"

int	main(void)
{
	std::string	string = "HI THIS IS BRAIN";
	std::string	*stringPTR = &string;
	std::string	stringREF = string;

	std::cout << "Content of String: " << string
		<< std::endl;
	std::cout << "Address of String: " << &string
		<< std::endl;
//	std::cout << "Pointer of String: " << *string
//		<< std::endl;

	std::cout << std::endl;

	std::cout << "Content of StringPTR: " << stringPTR
		<< std::endl;
	std::cout << "Address of StringPTR: " << &stringPTR
		<< std::endl;
	std::cout << "Pointer of StringPTR: " << *stringPTR
		<< std::endl;

	std::cout << std::endl;

	std::cout << "Content of StringREF: " << stringREF
		<< std::endl;
	std::cout << "Address of StringREF: " << &stringREF
		<< std::endl;
//	std::cout << "Pointer of StringREF: " << *stringREF
//		<< std::endl;

	return (0);
}
