// DListCursor.cpp
// Alex Harris
// 9/28/19

#include "DListCursor.hpp"

DListCursor::DListCursor()
{
	_head = nullptr;
	_cursor = nullptr;
	_tail = nullptr;
	_size = 0;
}

DListCursor::DListCursor(const DListCursor& source)
{
	_copy(source);
}

DListCursor& DListCursor::operator=(const DListCursor& source)
{
	// if the list isn't the same, make a copy
	if (this != &source) {
		_copy(source);
	}
	return *this;
}

ItemType DListCursor::operator[](size_t position) const
{
	std::shared_ptr<DListNode> node = _find(position);
	return node->_item;
}

ItemType& DListCursor::operator[](size_t position)
{
	std::shared_ptr<DListNode> node = _find(position);
	return node->_item;
}

bool DListCursor::cursorForward()
{
	// if the cursor isn't at the end or the list isn't empty return false
	if (_cursor == _tail) {
		return false;
	}
	else {
		// else move the cursor return true
		_cursor = _cursor->_next;
		return true;
	}
}

bool DListCursor::cursorBackward()
{
	// if the cursor isn't the at the beginning or the list isn't empty return false
	if (_cursor == _head) {
		return false;
	}
	else {
		// else move the cursor return true
		_cursor = _cursor->_prev.lock();
		return true;
	}
}

void DListCursor::insertAtHead(ItemType item)
{
	// if the list isn't empty 
	if (_size != 0) {
		std::shared_ptr<DListNode> newNode = std::make_shared<DListNode>(item, nullptr, _head);
		_head->_prev = newNode;
		_head = newNode;
		_size++;
	}
	else {
		append(item);
	}
}

ItemType DListCursor::removeAtHead()
{
	// save the node being delted
	std::shared_ptr<DListNode> node = _head;
	ItemType item = node->_item;
	// if somehing is after the head
	if (_head->_next != nullptr) {
		_head = _head->_next;
		_head->_prev.lock() = nullptr;
	}
	else {
		// list is empty
		_head = _tail = _cursor = nullptr;
	}
	// if the cursor was node removed
	if (_cursor == node) {
		// make the cursor the new head
		_cursor = _head;
	}
	_size--;
	return item;
}

void DListCursor::append(ItemType item)
{
	// make the new node
	std::shared_ptr<DListNode> newNode = std::make_shared<DListNode>(item);
	// if the list was empty, set everything to the new node
	if (_size == 0) {
		_head = newNode;
		_tail = newNode;
		_cursor = newNode;
	}
	else {
		// else make the tail point to the new node
		_tail->_next = newNode;
		// make the new node point to the current tail
		newNode->_prev = _tail;
		// change the tail to the new node
		_tail = newNode;
	}
	_size++;
}

ItemType DListCursor::pop()
{
	// save the node being deleted
	std::shared_ptr<DListNode> node = _tail;
	ItemType item = node->_item;
	// if there is an item before the tail
	if (_tail->_prev.lock() != nullptr) {
		// move tail back
		_tail = _tail->_prev.lock();
		// make the tail's next nullptr
		_tail->_next = nullptr;
		// if the cursor was the old tail, make it the new tail
		if (_cursor = node) {
			_cursor = _tail;
		}
	}
	else {
		// else the list is empty
		_head = _cursor = _tail = nullptr;
	}
	_size--;
	return node->_item;
}

void DListCursor::insertBeforeCursor(ItemType item)
{
	// if the cusor is the head or list is empty, insert at head
	if (_size == 0 || _cursor == _head) {
		insertAtHead(item);
		return;
	}
	// make new node with next being the cursor
	std::shared_ptr<DListNode> newNode = std::make_shared<DListNode>(item, nullptr, _cursor);
	// new node's prev is cursor's current prev
	newNode->_prev = _cursor->_prev.lock();
	// make cursor's prev the new node
	newNode->_prev.lock()->_next = newNode;
	// set the crusor's prev to the new node
	_cursor->_prev = newNode;
	_size++;
}

void DListCursor::insertAfterCursor(ItemType item)
{	
	// if the list is empty or the cursor is the tail, append
	if (_size == 0 || _cursor == _tail) {
		append(item);
		return;
	}
	// make new node with prev being the cursor
	std::shared_ptr<DListNode> newNode = std::make_shared<DListNode>(item, _cursor);
	// new node's next is cursor's current prev
	newNode->_next = _cursor->_next;
	// make cursor's prev the new node
	newNode->_next->_prev = newNode;
	// set the crusor's next to the new node
	_cursor->_next = newNode;
	_size++;
}

ItemType DListCursor::removeCursor()
{	
	// use other methods for cursor at beginning or end of list
	if (_cursor == _head) {
		return removeAtHead();
	}
	else if (_cursor == _tail) {
		return pop();
	}
	else {
		// save item to return later
		ItemType item = _cursor->_item;
		// set current cursor's prev's next to cursor's next
		_cursor->_prev.lock()->_next = _cursor->_next;
		// set current cursor's next's prev to cursor's prev
		_cursor->_next->_prev = _cursor->_prev;
		// move cursor forward
		_cursor = _cursor->_next;
		_size--;
		return item;
	}
}

void DListCursor::_copy(const DListCursor& source)
{
	// initialze node to head
	std::shared_ptr<DListNode> node = source._head;
	for (size_t i = 0; i < source._size; ++i) {
		this->append(node->_item);
		// if node is the cursor of the source 
		if (node == source._cursor) {
			// make that node the new list's cursor
			this->_cursor = this->_tail;
		}
		node = node->_next;
	}
}

std::shared_ptr<DListNode> DListCursor::_find(size_t position) const
{
	// step through the nodes till that position is found
	std::shared_ptr<DListNode> node = _head;
	for (size_t i = 0; i < position; ++i) {
		node = node->_next;
	}
	return node;
}
