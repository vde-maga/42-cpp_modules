#ifndef ARRAY_HPP
# define ARRAY_HPP

template <typename T> class Array
{
  private:
	T *_arr;
	unsigned int _size;

  public:
	Array(void);
	Array(unsigned int n);
	Array(const Array &src);
	~Array(void);

	Array &operator=(const Array &rhs);
	T &operator[](unsigned int idx);
	const T &operator[](unsigned int idx) const;

	unsigned int size(void) const;
};

# include "Array.tpp"

#endif