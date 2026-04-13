#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
    private:
        size_t  count;
        Contact contacts[8];

    public:
        PhoneBook();

        void    addContact(void);
        void    searchContact(void);
};

#endif