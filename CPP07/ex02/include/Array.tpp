#ifndef ARRAY_TPP
# define ARRAY_TPP

# include <stdexcept>

template <typename T> Array<T>::Array(void) : _arr(0), _size(0)
{
}

template <typename T> Array<T>::Array(unsigned int n) : _arr(new T[n]()),
	_size(n)
{
}

template <typename T> Array<T>::Array(const Array &src) : _arr(new T[src._size]()),
	_size(src._size)
{
	for (unsigned int i = 0; i < _size; ++i)
	{
		_arr[i] = src._arr[i];
	}
}

template <typename T> Array<T>::~Array(void)
{
	delete[] _arr;
}

template <typename T> Array<T> &Array<T>::operator=(const Array &rhs)
{
	T	*new_arr;

	if (this != &rhs)
	{
		new_arr = new T[rhs._size]();
		for (unsigned int i = 0; i < rhs._size; ++i)
		{
			new_arr[i] = rhs._arr[i];
		}
		delete[] _arr;
		_arr = new_arr;
		_size = rhs._size;
	}
	return (*this);
}

template <typename T> T &Array<T>::operator[](unsigned int idx)
{
	if (idx >= _size)
	{
		throw std::out_of_range("Array: index out of bounds");
	}
	return (_arr[idx]);
}

template <typename T> const T &Array<T>::operator[](unsigned int idx) const
{
	if (idx >= _size)
	{
		throw std::out_of_range("Array: index out of bounds");
	}
	return (_arr[idx]);
}

template <typename T> unsigned int Array<T>::size(void) const
{
	return (_size);
}

#endif