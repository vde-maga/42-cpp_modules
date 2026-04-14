#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
  private:
    size_t		_count; // Conta quantos contactos foram adicionados no total
    Contact		_contacts[8];

    // Métodos privados (encapsulamento - regra do subject)
    std::string	_getFormattedField(const std::string &field) const;
    void		_displayContactInfo(const Contact &contact) const;

  public:
    PhoneBook();

    void addContact();
    void searchContact();
};

#endif