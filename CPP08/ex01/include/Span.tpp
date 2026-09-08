#ifndef SPAN_TPP
# define SPAN_TPP

# include <iterator>

template <typename It> void Span::addNumbers(It first, It last)
{
	// Defensive programming: verifica a capacidade total ANTES de modificar o estado
	typename std::iterator_traits<It>::difference_type count = std::distance(first,
			last);
	if (static_cast<size_t>(count) > max - nums.size())
		throw TooManyElementsException();
	for (; first != last; ++first) // Pré-incremento aplicado
	{
		addNumber(*first);
	}
}

#endif
