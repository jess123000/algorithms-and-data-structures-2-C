// main.cpp
// Alex Harris
// 9/28/19

#include <cassert>
#define private public
#include "AVLTree.hpp"

using std::cerr;

int main() {
	AVLTree<int> tree;
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);
	cout << "Preorder:" << endl;
	tree.printPreorder();
	cout << "Inorder:" << endl;
	tree.printInorder();
	cout << "Postorder:" << endl;
	tree.printPostorder();
	assert(tree._root->_item == 2);
	cout << "Root correct." << endl;
	assert(tree._root->_left->_item == 1);
	cout << "Left correct." << endl;
	assert(tree._root->_right->_item == 3);
	cout << "Right correct." << endl;
	AVLTree<int> tree2;
	tree2.insert(3);
	tree2.insert(6);
	tree2.insert(8);
	tree2.insert(5);
	tree2.insert(7);
	assert(tree2._root->_item == 6);
	cout << "6 in right spot." << endl;
	assert(tree2._root->_left->_item == 3);
	cout << "3 in right spot." << endl;
	assert(tree2._root->_right->_item == 8);
	cout << "8 in right spot." << endl;
	assert(tree2._root->_left->_right->_item == 5);
	cout << "5 in right spot." << endl;
	assert(tree2._root->_right->_left->_item == 7);
	cout << "7 in right spot." << endl;
	cout << "insert tests passed." << endl;
	cout << "Preorder:" << endl;
	tree2.printPreorder();
	cout << "Inorder:" << endl;
	tree2.printInorder();
	cout << "Postorder:" << endl;
	tree2.printPostorder();
	assert(tree2.find(3)->_item == 3);
	cout << "Found worked correctly, found 3" << endl;
	assert(tree2.find(5)->_item == 5);
	cout << "Found worked correctly, found 5" << endl;
	assert(tree2.find(8)->_item == 8);
	cout << "Found worked correctly, found 8" << endl;
	assert(tree2.find(7)->_item == 7);
	cout << "Found worked correctly, found 7" << endl;
	assert(tree2.find(6)->_item == 6);
	cout << "Found worked correctly, found 6" << endl;
	assert(tree2.find(62) == nullptr);
	cout << "Found worked correctly, found nullptr" << endl;
	AVLTree<int> tree3;
	tree3 = tree;
	assert(tree3._root->_item == 2);
	cout << "Root correct." << endl;
	assert(tree3._root->_left->_item == 1);
	cout << "Left correct." << endl;
	assert(tree3._root->_right->_item == 3);
	cout << "Right correct." << endl; 
	cout << "_copyNodes test normal passed." << endl;
	AVLTree<int> tree4;
	tree3 = tree4;
	assert(tree3._root == nullptr);
	cout << "_copyNodes test empty passed." << endl;
	return 0;
}