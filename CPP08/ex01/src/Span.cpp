#include "../include/Span.hpp"
#include <algorithm>

// --- Span: Orthodox Canonical Form ---
Span::Span() : max(0)
{
}

Span::Span(unsigned int max) : max(max)
{
	nums.reserve(max);
}

Span::Span(const Span &other) : nums(other.nums), max(other.max)
{
}

Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		nums = other.nums;
		max = other.max;
	}
	return (*this);
}

Span::~Span()
{
}

// --- Span: Methods ---
void Span::addNumber(int num)
{
	if (nums.size() >= max)
		throw TooManyElementsException();
	nums.push_back(num);
}

unsigned int Span::shortestSpan() const
{
	if (nums.size() < 2)
		throw TooLittleElementsException();

	std::vector<int> copy = nums;
	std::sort(copy.begin(), copy.end());

	// Cast para unsigned int ANTES da subtração para evitar UB de overflow signed
	unsigned int min_span = static_cast<unsigned int>(copy[1])
		- static_cast<unsigned int>(copy[0]);

	for (size_t i = 2; i < copy.size(); ++i)
	{
		unsigned int current_span = static_cast<unsigned int>(copy[i])
			- static_cast<unsigned int>(copy[i - 1]);
		if (current_span < min_span)
			min_span = current_span;
	}
	return (min_span);
}

unsigned int Span::longestSpan() const
{
	if (nums.size() < 2)
		throw TooLittleElementsException();

	std::vector<int>::const_iterator min_it = std::min_element(nums.begin(),
			nums.end());
	std::vector<int>::const_iterator max_it = std::max_element(nums.begin(),
			nums.end());

	// Cast para unsigned int ANTES da subtração para evitar UB
	return (static_cast<unsigned int>(*max_it)
		- static_cast<unsigned int>(*min_it));
}

// --- Exceptions: Orthodox Canonical Form ---
// TooLittleElementsException
Span::TooLittleElementsException::TooLittleElementsException() throw()
{
}
Span::TooLittleElementsException::TooLittleElementsException(const TooLittleElementsException &other) throw() : std::exception(other)
{
}
Span::TooLittleElementsException &Span::TooLittleElementsException::operator=(const TooLittleElementsException &other) throw()
{
	if (this != &other)
		std::exception::operator=(other);
	return (*this);
}
Span::TooLittleElementsException::~TooLittleElementsException() throw()
{
}
const char *Span::TooLittleElementsException::what() const throw()
{
	return ("Too little elements");
}

// TooManyElementsException
Span::TooManyElementsException::TooManyElementsException() throw()
{
}
Span::TooManyElementsException::TooManyElementsException(const TooManyElementsException &other) throw() : std::exception(other)
{
}
Span::TooManyElementsException &Span::TooManyElementsException::operator=(const TooManyElementsException &other) throw()
{
	if (this != &other)
		std::exception::operator=(other);
	return (*this);
}
Span::TooManyElementsException::~TooManyElementsException() throw()
{
}
const char *Span::TooManyElementsException::what() const throw()
{
	return ("Too many elements");
}
