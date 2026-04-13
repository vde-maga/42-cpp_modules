#include "../includes/Contact.hpp"

void    Contact::setFirstName(std::string str)
{
    this->_firstName = str;
}

void    Contact::setLastName(std::string str)
{
    this->_lastName = str;
}

void    Contact::setNickname(std::string str)
{
    this->_nickname = str;
}

void    Contact::setPhoneNumber(std::string str)
{
    this->_phoneNumber = str;
}

void    Contact::setSecret(std::string str)
{
    this->_secret = str;
}

const std::string& Contact::getFirstName(void) const
{
    return (this->_firstName);
}

const std::string& Contact::getLastName(void) const
{
    return (this->_lastName);
}

const std::string& Contact::getNickname(void) const
{
    return (this->_nickname);
}

const std::string& Contact::getPhoneNumber(void) const
{
    return (this->_phoneNumber);
}

const std::string& Contact::getSecret(void) const
{
    return (this->_secret);
}