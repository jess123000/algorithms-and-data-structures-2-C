//
//  DListCursor.hpp
//  DListCursor
//
//  Created by David M. Reed on 4/2/19.
//  Copyright © 2019 David Reed. All rights reserved.
//

#ifndef DListCursor_hpp
#define DListCursor_hpp

#include "DListNode.hpp"

/**
 a list with a cursor implmented as nodes with pointers
 to the previous and next node to the list

 the insertion methods should never fail (unless computer
 runs out of memory) and the cursor should not change
 positions upon an insert unless the list was empty
 in which case the cursor points to the newly inserted node

 the head and tail point to the first and last, respectively
 nodes in the list unless the list is empty in which 
 case their value is nullptr
 */
class DListCursor {

public:
	// constructor
	DListCursor();

	// copy constructor
	DListCursor(const DListCursor& source);

	// assignment operator
	DListCursor& operator=(const DListCursor& source);

	/**
	 returns true if list is empty, false otherwise

	 @return true if list is empty, false otherwise
	 */
	bool isEmpty() const { return _size == 0; };

	/**
	 returns number of items in the list

	 @return number of items in the list
	 */
	int length() const { return _size; }

	/**
	 returns the item at position (0 is the start of the list)
	 in the list

	 @param position index position for item to return
	 @pre 0 <= position < length()
	 @return item at the specified position
	 */
	ItemType operator[](size_t position) const;

	/**
	 returns the item at position (0 is the start of the list)
	 in the list

	 @param position index position for item to return
	 @pre 0 <= position < length()
	 @return item at the specified position
	 */
	ItemType& operator[](size_t position);

	/**
	 returns item at the head

	 @pre list is not empty
	 @return first item in list
	 */ItemType itemAtHead() const { return _head->_item; }

	 /**
	  returns item at the cursor

	  @pre list is not empty
	  @return item at the cursor
	  */
	ItemType itemAtCursor() const { return _cursor->_item; }

	/**
	 returns item at the cursor

	 @pre list is not empty
	 @return item at end of the list
	 */
	ItemType itemAtTail() const { return _tail->_item; }

	/**
	 returns true if cursor at start of list (or list empty), false otherwise

	 @return true if cursor at start of list (or list empty), false otherwise
	 */
	bool isCursorAtHead() const { return _cursor == _head; }

	/**
	 returns true if cursor at end of list (or list empty), false otherwise

	 @return true if cursor at end of list (or list empty), false otherwise
	 */
	bool isCursorAtTail() const { return _cursor == _tail; }

	/**
	 moves cursor to start of list
	 */
	void cursorToHead() { _cursor = _head; }

	/**
	 moves cursor to end of list
	 */
	void cursorToTail() { _cursor = _tail; }

	/**
	 moves cursor forward one position if list not empty

	 @return true if cursor moved forward; false if cursor already at
	 end or list empty
	 */
	bool cursorForward();

	/**
	 moves cursor backward one position if list not empty

	 @return true if cursor moved backward; false if cursor already at beginning or list empty
	 */
	bool cursorBackward();

	/**
	 insert a value at the beginning of the list
	 @param item item to insert at beginning of list
	 */
	void insertAtHead(ItemType item);

	/**
	 remove and return last first in list

	 @pre the list is not empty
	 @return the item that was first in the list
	 */
	ItemType removeAtHead();

	/**
	 add item to end of list

	 @param item item to add
	 */
	void append(ItemType item);

	/**
	 remove and return last item in list

	 @pre the list is not empty
	 @return the item that was last in the list
	 */
	ItemType pop();

	/**
	 insert an item before the cursor

	 @param item item to insert
	 */
	void insertBeforeCursor(ItemType item);

	/**
	 insert an item before the cursor

	 @param item item to insert
	 */
	void insertAfterCursor(ItemType item);

	/**
	 remove and return the iterm at the cursor

	 @pre list is not empty
	 @post cursor is set to the next node unless there is
	 no next node in which case the cursor is set to the 
	 previous node; if the list is now empty cursor should 
	 be nullptr
	 @return the item that was at the cursor
	 */
	ItemType removeCursor();

private:
	// helper function for copy constructor and operator=
	void _copy(const DListCursor& source);

	/**
	 return the DListNode at the position in the list

	 @param position the index starting at zero of the node 
	 we want to return
	 @pre 0 <= position < length()
	 @return node at the specified position
	 */
	std::shared_ptr<DListNode> _find(size_t position) const;

	// pointers to the head, cursor, and tail nodes
	std::shared_ptr<DListNode> _head, _cursor, _tail;

	// number of items in the list
	int _size;
};

#endif /* DListCursor_hpp */
