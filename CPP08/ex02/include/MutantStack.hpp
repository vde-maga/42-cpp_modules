#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template <typename T> class MutantStack : public std::stack<T>
{
  public:
	// Orthodox Canonical Form
	MutantStack();
	MutantStack(const MutantStack &other);
	MutantStack &operator=(const MutantStack &other);
	~MutantStack();

	// Iterators
	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
};

# include "MutantStack.tpp"

#endif
