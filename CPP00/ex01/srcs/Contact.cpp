#include "Contact.hpp"

Contact::Contact()
{
}

// Setters
void Contact::setFirstName(const std::string &str)
{
	this->_firstName = str;
}
void Contact::setLastName(const std::string &str)
{
	this->_lastName = str;
}
void Contact::setNickname(const std::string &str)
{
	this->_nickname = str;
}
void Contact::setPhoneNumber(const std::string &str)
{
	this->_phoneNumber = str;
}
void Contact::setSecret(const std::string &str)
{
	this->_secret = str;
}

// Getters
const std::string &Contact::getFirstName() const
{
	return (this->_firstName);
}
const std::string &Contact::getLastName() const
{
	return (this->_lastName);
}
const std::string &Contact::getNickname() const
{
	return (this->_nickname);
}
const std::string &Contact::getPhoneNumber() const
{
	return (this->_phoneNumber);
}
const std::string &Contact::getSecret() const
{
	return (this->_secret);
}
