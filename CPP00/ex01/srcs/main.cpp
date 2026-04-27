#include "Colors.hpp"
#include "PhoneBook.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

static bool	safeGetline(std::string &out, const std::string &prompt)
{
	while (true)
	{
		std::cout << CYAN << prompt << RESET << std::flush;
		if (!std::getline(std::cin, out))
		{
			if (std::cin.eof())
			{
				std::cout << std::endl;
				return (false);
			}
			std::cin.clear();
			continue ;
		}
		return (true);
	}
}

static bool	getNonEmptyInput(std::string &out, const std::string &prompt)
{
	while (true)
	{
		if (!safeGetline(out, prompt))
			return (false);
		if (!out.empty())
			return (true);
		std::cout << RED << "Error: Field cannot be empty."
			<< RESET << std::endl;
	}
}

static bool	getPhoneNumberInput(std::string &out)
{
	while (true)
	{
		if (!getNonEmptyInput(out, "Phone Number: "))
			return (false);
		if (out.find_first_not_of("0123456789") == std::string::npos)
			return (true);
		std::cout << RED << "Error: Phone number must only contain digits."
			<< RESET << std::endl;
	}
}

static bool	promptAddContact(PhoneBook &phoneBook)
{
	Contact	newContact;

	std::string input;
	if (!getNonEmptyInput(input, "First Name: "))
		return (false);
	newContact.setFirstName(input);
	if (!getNonEmptyInput(input, "Last Name: "))
		return (false);
	newContact.setLastName(input);
	if (!getNonEmptyInput(input, "Nickname: "))
		return (false);
	newContact.setNickname(input);
	if (!getPhoneNumberInput(input))
		return (false);
	newContact.setPhoneNumber(input);
	if (!getNonEmptyInput(input, "Darkest Secret: "))
		return (false);
	newContact.setSecret(input);
	phoneBook.addContact(newContact);
	std::cout << GREEN << "Contact added successfully." << RESET << std::endl;
	return (true);
}

static std::string formatField(const std::string &field)
{
	if (field.length() > 10)
		return (field.substr(0, 9) + ".");
	return (field);
}

static void	displayContactDetails(const Contact &contact)
{
	std::cout << std::endl;
	std::cout << "First Name: " << contact.getFirstName() << std::endl;
	std::cout << "Last Name: " << contact.getLastName() << std::endl;
	std::cout << "Nickname: " << contact.getNickname() << std::endl;
	std::cout << "Phone Number: " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << contact.getSecret() << std::endl;
	std::cout << std::endl;
}

static bool promptSearchContact(PhoneBook &phoneBook)
{
	size_t	count = phoneBook.getCount();
	if (count == 0)
	{
		std::cout << YELLOW << "The phonebook is empty!"
			<< RESET << std::endl;
		return (true);
	}

	std::cout << MAGENTA << "\n|     Index|First Name| Last Name|  Nickname|"
		<< RESET << std::endl;
	std::cout << MAGENTA << "|----------|----------|----------|----------|"
		<< RESET << std::endl;

	for (size_t i = 0; i < count; i++)
	{
		const Contact* c = phoneBook.getContact(i);
		std::cout << "|" << std::right << std::setw(10) << i << "|";
		std::cout << std::right << std::setw(10) << formatField(c->getFirstName()) << "|";
		std::cout << std::right << std::setw(10) << formatField(c->getLastName()) << "|";
		std::cout << std::right << std::setw(10) << formatField(c->getNickname()) << "|";
		std::cout << std::endl;
	}

	std::string input;
	while (true)
	{
		if (!safeGetline(input, "\nEnter index to display: "))
			return (false);

		std::istringstream	iss(input);
		int	index;
		if (iss >> index && iss.eof() && index >= 0 && static_cast<size_t>(index) < count)
		{
			const Contact* c = phoneBook.getContact(static_cast<size_t>(index));
			if (c != NULL)
			{
				displayContactDetails(*c);
				break;
			}
		}
		std::cout << RED << "Error: Invalid index." << RESET << std::endl;
	}
	return (true);
}

int	main(void)
{
	PhoneBook	phoneBook;

	std::cout << GREEN << "Phone Book" << RESET << std::endl;
	std::cout << MAGENTA << "ADD" << RESET;
	std::cout << " | ";
	std::cout << CYAN << "SEARCH" << RESET;
	std::cout << " | ";
	std::cout << RED << "EXIT" << RESET << std::endl;
	while (true)
	{
		std::string userInput;
		if (!safeGetline(userInput, GREEN "PhoneBook> " RESET))
			break ;
		if (userInput == "ADD")
		{
			if (!promptAddContact(phoneBook))
				break ;
		}
		else if (userInput == "SEARCH")
		{
			if (!promptSearchContact(phoneBook))
				break ;
		}
		else if (userInput == "EXIT")
		{
			break ;
		}
	}
	return (0);
}
