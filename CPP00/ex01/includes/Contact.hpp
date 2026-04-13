#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact
{
    private:
        std::string _firstName;
        std::string _lastName;
        std::string _nickname;
        std::string _phoneNumber;
        std::string _secret;

    public:
        void    setFirstName(std::string str);
        void    setLastName(std::string str);
        void    setNickname(std::string str);
        void    setPhoneNumber(std::string str);
        void    setSecret(std::string str);

        const std::string&    getFirstName(void) const;
        const std::string&    getLastName(void) const;
        const std::string&    getNickname(void) const;
        const std::string&    getPhoneNumber(void) const;
        const std::string&    getSecret(void) const;

};

#endif