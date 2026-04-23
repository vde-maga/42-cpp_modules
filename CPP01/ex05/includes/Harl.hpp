#ifndef HARL_HPP
# define HARL_HPP

# include <string>

class Harl
{
	private:
		typedef void (Harl::*HarlFunc)(void) const;

		struct			ComplainLevel
		{
			const std::string name;
			HarlFunc	func;
		};

		void debug(void) const;
		void info(void) const;
		void warning(void) const;
		void error(void) const;

	public:
		Harl(void);
		Harl(const Harl &src);
		Harl &operator=(const Harl &rhs);
		~Harl(void);

		void complain(const std::string &level) const;
};

#endif
