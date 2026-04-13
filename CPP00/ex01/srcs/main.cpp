#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include "../includes/PhoneBook.hpp"

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m"
#define GREEN   "\033[1m\033[32m" 
#define MAGENTA "\033[1m\033[35m" 
#define CYAN    "\033[1m\033[36m" 
#define YELLOW  "\033[1m\033[33m"

int isInputValid(const std::string& input)
{
    return (input == "ADD" || input == "SEARCH" || input == "EXIT");
}

std::string getUserInput(void)
{
    std::string input;

    while (1)
    {
        std::cout << "PhoneBook> ";
        getline(std::cin, input);
        if (std::cin.eof() == true)
        {
            std::cin.clear();
            clearerr(stdin);
        }
        if (!input.empty() && isInputValid(input) == 1)
            break;
        std::cin.clear();
        std::cout << "Please insert a valid input" << std::endl;
    }
    return (input);
}

int main(void)
{
    PhoneBook phoneBook;
    std::string userInput;

    std::cout << GREEN << "Phone Book" << RESET << std::endl;
    std::cout << MAGENTA << "ADD" << RESET;
    std::cout << " | ";
    std::cout << CYAN << "SEARCH" << RESET;
    std::cout << " | ";
    std::cout << RED << "EXIT" << RESET << std::endl;
    while (1)
    {
        userInput = getUserInput();
        if (userInput == "ADD")
            phoneBook.addContact();
        else if (userInput == "SEARCH")
            phoneBook.searchContact();
        else
            return (0);
    }
    return (0);
}