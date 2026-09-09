#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <deque>
# include <exception>
# include <iostream>
# include <sys/time.h>
# include <vector>

class PmergeMe
{
  private:
	std::vector<int> vec_;
	std::deque<int> deq_;

	std::vector<int> original_vec_;
	std::deque<int> original_deq_;

	void sortVector();
	void sortDeque();

	void sortVectorRecursive(std::vector<int> &indices);
	void sortDequeRecursive(std::deque<int> &indices);

	PmergeMe();

  public:
	explicit PmergeMe(const std::vector<int> &input);
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();

	void run();

	class PmergeMeException : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};
};

#endif
