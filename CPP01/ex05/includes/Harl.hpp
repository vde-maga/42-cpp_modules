#ifndef HARL_HPP
# define HARL_HPP

# include <string>

class Harl
{
  private:
	typedef void (Harl::*HarlFunc)(void) const;

	struct						ComplainLevel
	{
		const char *const name;
		HarlFunc				func;
	};

	static const ComplainLevel	levels[];
	static const int			num_levels;

	void debug(void) const;
	void info(void) const;
	void warning(void) const;
	void error(void) const;

  public:
	Harl(void);
	~Harl(void);

	void complain(const std::string &level) const;
};

#endif
