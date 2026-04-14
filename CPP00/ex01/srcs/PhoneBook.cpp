#include "../includes/Colors.hpp"
#include "../includes/PhoneBook.hpp"
#include <cstdio> // para clearerr
#include <cstdlib>
#include <iomanip>
#include <iostream>

// --- Funções Auxiliares de Input (Estáticas para não poluir o .hpp) ---

// Lê uma linha, garante que não está vazia e protege contra EOF (Ctrl+D)
static std::string getNonEmptyInput(const std::string &prompt)
{
	std::string input;
	while (true)
	{
		std::cout << CYAN << prompt << RESET << std::flush;
		if (!std::getline(std::cin, input))
		{
			if (std::cin.eof())
			{
				std::cin.clear();
				clearerr(stdin);
				std::cout << std::endl;
				continue ;
					// Tenta ler novamente (comum na 42 quando o Moulinette envia EOF)
			}
			std::cin.clear();
		}
		if (!input.empty())
			return (input);
		std::cout << RED << "Error: Field cannot be empty." << RESET << std::endl;
	}
}

// Lê e valida o número de telefone
static std::string getPhoneNumberInput()
{
	std::string input;
	while (true)
	{
		input = getNonEmptyInput("Phone Number: ");
		if (input.find_first_not_of("0123456789") == std::string::npos)
			return (input);
		std::cout << RED << "Error: Phone number must only contain digits." << RESET << std::endl;
	}
}

// --- Métodos da Classe PhoneBook ---

PhoneBook::PhoneBook() : _count(0)
{
}

std::string PhoneBook::_getFormattedField(const std::string &field) const
{
	if (field.length() > 10)
		return (field.substr(0, 9) + ".");
	return (field);
}

void PhoneBook::_displayContactInfo(const Contact &contact) const
{
	std::cout << std::endl;
	std::cout << "First Name: " << contact.getFirstName() << std::endl;
	std::cout << "Last Name: " << contact.getLastName() << std::endl;
	std::cout << "Nickname: " << contact.getNickname() << std::endl;
	std::cout << "Phone Number: " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << contact.getSecret() << std::endl;
	std::cout << std::endl;
}

void PhoneBook::addContact()
{
	Contact	newContact;
	size_t	insertIndex;

	newContact.setFirstName(getNonEmptyInput("First Name: "));
	newContact.setLastName(getNonEmptyInput("Last Name: "));
	newContact.setNickname(getNonEmptyInput("Nickname: "));
	newContact.setPhoneNumber(getPhoneNumberInput());
	newContact.setSecret(getNonEmptyInput("Darkest Secret: "));
	// Lógica Circular (Ring Buffer)
	// Se _count for 8, substitui o índice 0 (o mais antigo). Se 9, o índice 1, etc.
	insertIndex = this->_count % 8;
	this->_contacts[insertIndex] = newContact;
	this->_count++;
	std::cout << GREEN << "Contact added successfully ✅" << RESET << std::endl;
}

void PhoneBook::searchContact()
{
	// Calcula quantos contactos estão ativos no máximo (limitado a 8)
	size_t activeCount = (this->_count > 8) ? 8 : this->_count;

	if (activeCount == 0)
	{
		std::cout << YELLOW << "The phonebook is empty!" << RESET << std::endl;
		return ;
	}

	std::cout << MAGENTA << "\n|     Index|First Name| Last Name|  Nickname|" << RESET << std::endl;
	std::cout << MAGENTA << "|----------|----------|----------|----------|" << RESET << std::endl;

	for (size_t i = 0; i < activeCount; i++)
	{
		std::cout << "|" << std::right << std::setw(10) << i << "|";
		std::cout << std::right << std::setw(10) << this->_getFormattedField(this->_contacts[i].getFirstName()) << "|";
		std::cout << std::right << std::setw(10) << this->_getFormattedField(this->_contacts[i].getLastName()) << "|";
		std::cout << std::right << std::setw(10) << this->_getFormattedField(this->_contacts[i].getNickname()) << "|";
		std::cout << std::endl;
	}

	// Obtenção e validação do índice
	std::string input;
	int index = -1;
	while (true)
	{
		std::cout << CYAN << "\nEnter index to display: " << RESET << std::flush;
		if (!std::getline(std::cin, input))
		{
			if (std::cin.eof())
			{
				std::cin.clear();
				clearerr(stdin);
				std::cout << std::endl;
			}
			continue ;
		}
		if (!input.empty()
			&& input.find_first_not_of("0123456789") == std::string::npos)
		{
			index = std::atoi(input.c_str());
			// Protege contra números negativos (atoi("-1") falhava no size_t) e fora do limite
			if (index >= 0 && static_cast<size_t>(index) < activeCount)
				break ;
		}
		std::cout << RESET << "Error: Invalid index." << RESET << std::endl;
	}

	this->_displayContactInfo(this->_contacts[index]);
}