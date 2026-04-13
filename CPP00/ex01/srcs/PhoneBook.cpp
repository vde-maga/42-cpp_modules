#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "../includes/PhoneBook.hpp"

std::string getFormattedField(const std::string& field)
{
	if (field.length() > 10)
		return field.substr(0,9) + ".";
	return field;
}

void display_contact_info(Contact contact)
{
	std::cout << std::endl;
	std::cout << "FirstName: " << contact.getFirstName() << std::endl;
	std::cout << "LastName: " << contact.getLastName() << std::endl;
	std::cout << "Nickname: " << contact.getNickname() << std::endl;
	std::cout << "PhoneNumber: " << contact.getPhoneNumber() << std::endl;
	std::cout << "Secret: " << contact.getSecret() << std::endl;
	std::cout << std::endl;
}

// Default constructor
PhoneBook::PhoneBook() : count(0) {};

void PhoneBook::addContact(void)
{
	Contact	new_contact;
	std::string	input;

	std::cout << "FirstName: ";
	getline(std::cin, input);
	new_contact.setFirstName(input);

	std::cout << "LastName: ";
	getline(std::cin, input);
	new_contact.setLastName(input);

	std::cout << "Nickname: ";
	getline(std::cin, input);
	new_contact.setNickname(input);

	while (1)
	{
		std::cout << "Phonenumber: ";
		getline(std::cin, input);
		if (!input.empty() && input.find_first_not_of("0123456789") != std::string::npos) 
		{
			std::cin.clear();
			std::cout << "Phone number must only contain numbers" << std::endl;
			continue;
		}
		new_contact.setPhoneNumber(input);
		break;
	}

	std::cout << "Darkest Secret: ";
	getline(std::cin, input);
	new_contact.setSecret(input);

	if (count > 7)
		this->contacts[count - 1] = new_contact;
	else
	{
		this->count += 1;
		this->contacts[count - 1] = new_contact;
	}
	std::cout << "Contact added successfully ✅" << std::endl;
}

void PhoneBook::searchContact(void)
{
	if (count == 0)
	{
		std::cout << "There are no contacts to display!" << std::endl;
		return ;
	}
	std::cout << "\n|     Index|First Name| Last Name|  Nickname|" << std::endl;
	for (size_t i = 0; i < this->count; i += 1)
	{
		std::cout << "|" << std::right << std::setw(10) << i << "|";
		std::cout << std::right << std::setw(10) << getFormattedField(contacts[i].getFirstName()) << "|" ;
		std::cout << std::right << std::setw(10) << getFormattedField(contacts[i].getLastName()) << "|";
		std::cout << std::right << std::setw(10) << getFormattedField(contacts[i].getNickname()) << "|";
		std::cout << std::endl;
	}

	std::string index;
	int conv_index;

	while (1)
	{
		std::cout << "Please insert the index of the contact you'd like to display: ";
		getline(std::cin, index);
		if (!index.empty() && index.find_first_not_of("0123456789") == std::string::npos)
		{
			conv_index = atoi(index.c_str());
			if (conv_index <= 7)
				break;
		}
		std::cin.clear();
		std::cout << "Invalid input" << std::endl;
	}
	if ((size_t)conv_index > (count - 1))
		std::cout << "Error: No contact with that index" << std::endl;
	else
		display_contact_info(this->contacts[conv_index]);
}