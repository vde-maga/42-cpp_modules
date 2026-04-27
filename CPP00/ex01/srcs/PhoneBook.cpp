#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _count(0)
{
}

void PhoneBook::addContact(const Contact &contact)
{
	size_t	insertIndex;

	insertIndex = this->_count % MAX_CONTACTS;
	this->_contacts[insertIndex] = contact;
	this->_count++;
}

const Contact *PhoneBook::getContact(size_t index) const
{
	size_t activeCount = (this->_count > MAX_CONTACTS) ? MAX_CONTACTS : this->_count;
	if (index >= activeCount)
		return (NULL);
	return (&(this->_contacts[index]));
}

size_t PhoneBook::getCount() const
{
	return ((this->_count > MAX_CONTACTS) ? MAX_CONTACTS : this->_count);
}
