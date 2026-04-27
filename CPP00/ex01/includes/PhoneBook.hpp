#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
  private:
	static const size_t MAX_CONTACTS = 8;
	size_t _count;
	Contact _contacts[8];

  public:
	PhoneBook();

	void addContact(const Contact &contact);
	const Contact *getContact(size_t index) const;
	size_t getCount() const;
};

#endif
