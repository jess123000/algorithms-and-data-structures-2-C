//
//  BinaryTreeNode.hpp
//  AVLTreeTemplate
//
//  Created by David M Reed on 6/12/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef BinaryTreeNode_h
#define BinaryTreeNode_h

#include <memory>

template <typename T>
class BinaryTreeNode {

    template<typename> friend class AVLTree;
    template<typename> friend int getHeight(const std::shared_ptr<BinaryTreeNode<T>> node);

public:
    BinaryTreeNode(const T &item, const std::shared_ptr<BinaryTreeNode<T>> &left = nullptr, const std::shared_ptr<BinaryTreeNode<T>> &right = nullptr, const int height = 0);

    int height() const { return _height; }
    void setHeight(const int height) { _height = height; }
    T item() const { return _item; }

private:
    T _item;
    std::shared_ptr<BinaryTreeNode<T>> _left, _right;
    int _height;
};

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T &item, const std::shared_ptr<BinaryTreeNode<T>> &left, const std::shared_ptr<BinaryTreeNode<T>> &right, const int height) {
    _item = item;
    _left = left;
    _right = right;
    _height = height;
}

template <typename T>
int getHeight(const std::shared_ptr<BinaryTreeNode<T>> node)
{
    if (!node)
        return -1;
    else
        return node->height();
}

#endif /* BinaryTreeNode_h */
