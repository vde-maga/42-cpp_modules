#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
  private:
    size_t		_count;
    Contact		_contacts[8];

    std::string	_getFormattedField(const std::string &field) const;
    void		_displayContactInfo(const Contact &contact) const;

  public:
    PhoneBook();

    void addContact();
    void searchContact();
};

#endif