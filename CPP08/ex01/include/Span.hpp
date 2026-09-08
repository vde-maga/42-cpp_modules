#ifndef SPAN_HPP
# define SPAN_HPP

# include <exception>
# include <iterator>
# include <vector>

class Span
{
  private:
	std::vector<int> nums;
	unsigned int max;

	Span(); // Construtor por defeito privado (YAGNI)

  public:
	Span(unsigned int max);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();

	void addNumber(int num);

	template <typename It> void addNumbers(It first, It last);

	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;

	class TooLittleElementsException : public std::exception
	{
		public:
		TooLittleElementsException() throw();
		TooLittleElementsException(const TooLittleElementsException &other) throw();
		TooLittleElementsException &operator=(const TooLittleElementsException &other) throw();
		virtual ~TooLittleElementsException() throw();
		virtual const char *what() const throw();
	};

	class TooManyElementsException : public std::exception
	{
		public:
		TooManyElementsException() throw();
		TooManyElementsException(const TooManyElementsException &other) throw();
		TooManyElementsException &operator=(const TooManyElementsException &other) throw();
		virtual ~TooManyElementsException() throw();
		virtual const char *what() const throw();
	};
};

# include "Span.tpp"

#endif
