#ifndef REPLACER_HPP
# define REPLACER_HPP

# include <string>

class Replacer
{
  public:
	Replacer(const std::string &filename, const std::string &s1,
		const std::string &s2);
	~Replacer();

	bool execute() const;

  private:
	const std::string _filename;
	const std::string _s1;
	const std::string _s2;

	std::string _replaceString(const std::string &content) const;

	// C++98 way to disable copy constructor and assignment operator (SOLID/SOC)
	Replacer(const Replacer &);
	Replacer &operator=(const Replacer &);
};

#endif
