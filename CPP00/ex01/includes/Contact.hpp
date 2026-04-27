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
	Contact();

	void setFirstName(const std::string &str);
	void setLastName(const std::string &str);
	void setNickname(const std::string &str);
	void setPhoneNumber(const std::string &str);
	void setSecret(const std::string &str);

	const std::string &getFirstName() const;
	const std::string &getLastName() const;
	const std::string &getNickname() const;
	const std::string &getPhoneNumber() const;
	const std::string &getSecret() const;
};

#endif
