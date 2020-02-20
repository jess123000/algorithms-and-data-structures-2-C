// List.hpp
// 08/29/19
// Alex Harris

#ifndef _LIST_H_
#define _LIST_H_

#include <cstdlib>
#include <memory>

class List {

public:

	List(size_t capacity = 10);
	/**
	constructor
	initialize empty list with the specified initial capaciy
	@param capacity initial capaciy of the list
	*/

	List(const List& source);
	/**
	copy constructor
	@post makes a deep copy of the source List
	@param source List to copy
	*/

	List& operator=(const List& source);
	/**
	assignment operator that makes a deep copy
	@post this is now a deep copy of the soure
	@param source List to copy
	@return deep copy of the source
	*/

	void append(const int item);
	/**
	append item onto the list
	@param item value to append onto the list
	*/

	int operator [] (size_t pos) const;
	/**
	return value at specified position
	@param pos position / index to access
	@return value at specified position / index
	*/

	int& operator [] (size_t pos);
	/**
	return value at specified position (as an l- value )
	@param pos position / index
	@return value at specified position / index
	*/

	size_t size() const { return _size; }
	/**
	returns number of elements in the list
	@return number of elements in the list
	*/


private:
	void copy(const List& source);
	void resize(size_t newSize);
	std::unique_ptr <int[]> _data;
	size_t _size;
	size_t _capacity;
};

inline int& List::operator[](size_t pos)
{
	return _data[pos];
}

inline int List::operator[](size_t pos) const
{
	return _data[pos];
}

#endif // _LIST_H_