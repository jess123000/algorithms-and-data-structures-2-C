//	Alex Harris
//  AVLTree.hpp
//  AVLTreeTemplate
//
//  Created by David M Reed on 6/12/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef AVLTree_h
#define AVLTree_h

#include "BinaryTreeNode.hpp"
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class AVLTree {
public:
    AVLTree();

    AVLTree(const AVLTree &source);

    AVLTree& operator=(const AVLTree &source);

    /// inserts item into the tree
    /// @param item item to be inserted
    void insert(const T &item);

    /// finds the node with the specified item
    /// @param item value to find in the tree
    /// @return the node where item is or nullptr if item is not in the tree
    std::shared_ptr<BinaryTreeNode<T>> find(const T &item);

    int size() const { return _size; }


    /// outputs the tree items use preorder traversal
    void printPreorder();

    /// outputs the tree items use inorder traversal
    void printInorder();

    /// outputs the tree items use postorder traversal
    void printPostorder();

private:
    // MARK: private helper methods


    /// makes a deepcopy of the subtree rooted at rootNode
    /// @param rootNode root of the subtree that it makes a deep copy of
    /// @return newly created deep copy of the rootNode subtree
    std::shared_ptr<BinaryTreeNode<T>> _copyNodes(const std::shared_ptr<BinaryTreeNode<T>> &rootNode);


    /// inserting item into the tree rooted at node
    /// @param node root of the subtree to insert item into
    /// @param item value to insert into tree
    void _insertHelp(std::shared_ptr<BinaryTreeNode<T>> &node, const T &item);

    /// see book for rotation details
    void _leftSingleRotate(std::shared_ptr<BinaryTreeNode<T>> &node);
    void _rightSingleRotate(std::shared_ptr<BinaryTreeNode<T>> &node);
    void _rightLeftRotate(std::shared_ptr<BinaryTreeNode<T>> &node);
    void _leftRightRotate(std::shared_ptr<BinaryTreeNode<T>> &node);


    /// return node of subtree containing item
    /// @param node root of subtree to search for the item
    /// @param item value to find
    std::shared_ptr<BinaryTreeNode<T>> _findHelp(const std::shared_ptr<BinaryTreeNode<T>> &node, const T &item);

    /// helpers for tree traversals
    void printInorderHelp(const std::shared_ptr<BinaryTreeNode<T>> &node);
    void printPreorderHelp(const std::shared_ptr<BinaryTreeNode<T>> &node);
    void printPostorderHelp(const std::shared_ptr<BinaryTreeNode<T>> &node);


    // MARK: data
    /// root of the tree
    std::shared_ptr<BinaryTreeNode<T>> _root;
    // number of elements in the tree
    int _size;
};

// maximum function for use with tree heights
inline int max(int a, int b)
{
    return a > b ? a : b;
}

template <typename T>
AVLTree<T>::AVLTree() {
	_root = nullptr;
	_size = 0;
}

template<typename T>
AVLTree<T>::AVLTree(const AVLTree& source)
{
	_root = _copyNodes(source._root);
	_size = source._size;
}

template<typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree& source)
{
	// if it's not itself
	if (this != &source) {
		_root = _copyNodes(source._root);
		_size = source._size;
	}
	return *this;
}

template<typename T>
void AVLTree<T>::insert(const T& item)
{
	_insertHelp(_root, item);
	// increase the size
	_size++;
}

template<typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::find(const T& item)
{
	return _findHelp(_root, item);
}

template<typename T>
void AVLTree<T>::printPreorder()
{
	printPreorderHelp(_root);
}

template<typename T>
void AVLTree<T>::printInorder()
{
	printInorderHelp(_root);
}

template<typename T>
void AVLTree<T>::printPostorder()
{
	printPostorderHelp(_root);
}

template<typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::_copyNodes(const std::shared_ptr<BinaryTreeNode<T>>& rootNode)
{
	// initialize variables
	std::shared_ptr<BinaryTreeNode<T>> leftNodes;
	std::shared_ptr<BinaryTreeNode<T>> rightNodes;
	std::shared_ptr<BinaryTreeNode<T>> newNode;
	// if tree being copied is empty, return a nullptr
	if (rootNode == nullptr) {
		return nullptr;
	}
	// else if we're at the bottom of a tree
	else if (rootNode->_left == nullptr && rootNode->_right == nullptr) {
		// create and return that node
		newNode = std::make_shared<BinaryTreeNode<T>>(rootNode->_item);
		return newNode;
	}
	else {
		newNode = std::make_shared<BinaryTreeNode<T>>(rootNode->_item);
		// if nothing on the right, go left
		if (rootNode->_right == nullptr) {
			leftNodes = _copyNodes(rootNode->_left);
			// assign left nodes to current node
			newNode->_left = leftNodes;
		}
		// if nothing on the left, go right
		else if (rootNode->_left == nullptr) {
			rightNodes = _copyNodes(rootNode->_right);
			// assign right nodes to current node
			newNode->_right = rightNodes;
		}
		// else go both ways
		else {
			leftNodes = _copyNodes(rootNode->_left);
			// assign left nodes to current node
			newNode->_left = leftNodes;
			rightNodes = _copyNodes(rootNode->_right);
			// assign right nodes to current node
			newNode->_right = rightNodes;
		}
		return newNode;
	}
}

template<typename T>
void AVLTree<T>::_insertHelp(std::shared_ptr<BinaryTreeNode<T>>& node, const T& item)
{
	// if node it nullptr we're where we need to be in the tree
	if (node == nullptr) {
		node = std::make_shared<BinaryTreeNode<T>>(item);
	}
	// else if the item is smaller, go to the left
	else if (item < node->_item) {
		_insertHelp(node->_left, item);
		// left subtree height may now be larger than right subtree
		if (getHeight(node->_left) - getHeight(node->_right) == 2) {
			// determine which subtree the new value was inserted
			if (item < node->_left->_item) {
				// insertion into left subtree of left child
				_leftSingleRotate(node);
			}
			else {
				_rightLeftRotate(node);
			}
		}
	}
	// else item is larger, go to the right
	else {
		_insertHelp(node->_right, item);
		// right subtree height may now be larger than left subtree
		if (getHeight(node->_right) - getHeight(node->_left) == 2) {
			// determine which subtree the new value was inserted
			if (item > node->_right->_item) {
				// insertion into left subtree of left child
				_rightSingleRotate(node);
			}
			else {
				_leftRightRotate(node);
			}
		}
	}
	// update height of tree rooted at node
	node->_height = max(getHeight(node->_left), getHeight(node->_right)) + 1;
}

template<typename T>
void AVLTree<T>::_leftSingleRotate(std::shared_ptr<BinaryTreeNode<T>>& node)
{
	// initialize parent and grandarent
	auto grandparent = node;
	auto parent = node->_left;

	// make grandparent's left, parent's right
	grandparent->_left = parent->_right;
	// make parent's right, the  new grandparent
	parent->_right = grandparent;
	// node to be parent
	node = parent;

	// find the height of parent and grandparent
	grandparent->_height = max(getHeight(grandparent->_left), getHeight(grandparent->_right)) + 1;
	parent->_height = max(getHeight(parent->_left), getHeight(parent->_right)) + 1;
}

template<typename T>
void AVLTree<T>::_rightSingleRotate(std::shared_ptr<BinaryTreeNode<T>>& node)
{
	// initialize parent and grandarent
	auto grandparent = node;
	auto parent = node->_right;

	// make grandparent's right, parent's left
	grandparent->_right = parent->_left;
	// make parent's left, the  new grandparent
	parent->_left = grandparent;
	// node to be parent
	node = parent;

	// find the height of parent and grandparent
	grandparent->_height = max(getHeight(grandparent->_right), getHeight(grandparent->_left)) + 1;
	parent->_height = max(getHeight(parent->_right), getHeight(parent->_left)) + 1;
}

template<typename T>
void AVLTree<T>::_rightLeftRotate(std::shared_ptr<BinaryTreeNode<T>>& node)
{
	_leftSingleRotate(node);
	_rightSingleRotate(node->_left);
}

template<typename T>
void AVLTree<T>::_leftRightRotate(std::shared_ptr<BinaryTreeNode<T>>& node)

{
	_rightSingleRotate(node);
	_leftSingleRotate(node->_right);
}

template<typename T>
std::shared_ptr<BinaryTreeNode<T>> AVLTree<T>::_findHelp(const std::shared_ptr<BinaryTreeNode<T>>& node, const T& item)
{
	// if we have the right node return it
	if (item == node->_item) {
		return node;
	}
	// else if the node isn't found return nullptr
	else if (item < node->_item && node->_left == nullptr) {
		return nullptr;
	}
	else if (item > node->_item && node->_right == nullptr) {
		return nullptr;
	}
	// else if item is snaller, go left
	else if (item < node->_item) {
		return _findHelp(node->_left, item);
	}
	// else item is bigger, go right
	else {
		return _findHelp(node->_right, item);
	}
}

template<typename T>
void AVLTree<T>::printInorderHelp(const std::shared_ptr<BinaryTreeNode<T>>& node)
{
	// go down the left if there is a left
	if (node->_left != nullptr) {
		printInorderHelp(node->_left);
	}
	// print the current node
	cout << node->_item << endl;
	// go down the right if there is a right
	if (node->_right != nullptr) {
		printInorderHelp(node->_right);
	}
}

template<typename T>
void AVLTree<T>::printPreorderHelp(const std::shared_ptr<BinaryTreeNode<T>>& node)
{
	// print the current node
	cout << node->_item << endl;
	// go down the left if there is a left
	if (node->_left != nullptr) {
		printPreorderHelp(node->_left);
	}
	// go down the right if there is a right
	if (node->_right != nullptr) {
		printPreorderHelp(node->_right);
	}
}

template<typename T>
void AVLTree<T>::printPostorderHelp(const std::shared_ptr<BinaryTreeNode<T>>& node)
{	
	// go down the left if there is a left
	if (node->_left != nullptr) {
		printPostorderHelp(node->_left);
	}
	// go down the right if there is a right
	if (node->_right != nullptr) {
		printPostorderHelp(node->_right);
	}
	// print the current node
	cout << node->_item << endl;
}

#endif /* AVLTree_h */
