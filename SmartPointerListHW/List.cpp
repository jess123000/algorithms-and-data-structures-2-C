// List.cpp
// Alex Harris
#include "List.hpp"

List::List(size_t capacity) {
	_data = std::make_unique <int[]>(capacity);
	_size = 0;
	_capacity = capacity;
}

List::List(const List& source) {
	copy(source);
}

void List::copy(const List& source) {
	for (size_t i = 0; i < source._size; ++i) {
		append(source._data[i]);
	}
}

List& List::operator=(const List& source) {
	if (this != &source) {
		copy(source);
	}
	return *this;
}

void List::append(const int item) {
	if (_size == _capacity) {
		resize(2 * _capacity);
	}
	_data[_size] = item;
	_size++;
}

void List::resize(size_t newSize) {
	std::unique_ptr <int[]> temp;
	temp = std::make_unique <int[]>(newSize);
	for (size_t i = 0; i < _capacity; ++i) {
		temp[i] = _data[i];
	}
	_data.swap(temp);
	_capacity = newSize;
}