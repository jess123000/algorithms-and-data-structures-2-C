// main.cpp
// Alex Harris
// 9/28/19

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <cassert>

#include "DListCursor.hpp"


int main() {
	DListCursor list1;
	int i;
	int item;
	for (i = 0; i < 5; ++i) {
		list1.append(i);
	}
	for (i = 0; i < 5; ++i) {
		assert(list1[i] == i);
	}
	cout << "Append and [] test passed." << endl;
	DListCursor list2;
	list2 = list1;
	for (i = 0; i < 5; ++i) {
		assert(list1[i] == list2[i]);
	}
	cout << "Copy test passed." << endl;
	for (i = 1; i < 5; ++i) {
		list1.cursorForward();
		assert(list1.itemAtCursor() == i);
	}
	cout << "Cursor Forward test passed." << endl;
	item = list1.pop();
	assert(item == 4);
	assert(list1.itemAtTail() == 3);
	assert(list1.itemAtCursor() == 3);
	assert(list1.length() == 4);
	cout << "Pop test passed." << endl;
	for (i = 2; i > -1; --i) {
		list1.cursorBackward();
		assert(list1.itemAtCursor() == i);
	}
	cout << "Cursor Backward test passed." << endl;
	item = list1.removeAtHead();
	assert(item == 0);
	assert(list1.itemAtHead() == 1);
	assert(list1.itemAtCursor() == 1);
	assert(list1.length() == 3);
	cout << "Remove Head test passed." << endl;
	list1.cursorForward();
	item = list1.removeCursor();
	assert(item == 2);
	assert(list1.itemAtHead() == 1);
	assert(list1.itemAtCursor() == 3);
	assert(list1.itemAtTail() == 3);
	assert(list1.length() == 2);
	cout << "Remove Cursor test passed." << endl;
	item = list1.removeAtHead();
	assert(item == 1);
	assert(list1.itemAtHead() == 3);
	assert(list1.itemAtCursor() == 3);
	assert(list1.itemAtTail() == 3);
	assert(list1.length() == 1);
	cout << "Remove Head test 2 passed." << endl;
	list1.insertAfterCursor(5);
	list1.insertAfterCursor(4);
	list1.insertBeforeCursor(1);
	list1.insertBeforeCursor(2);
	list1.insertAtHead(0);
	for (i = 0; i < 6; ++i) {
		assert(list1[i] == i);
	}
	cout << "Insert At Head, Before and After Cursor test passed." << endl;
	return 0;
}