#ifndef EX00_ADVCPP_BINARYSEARCHTREE_IMP_H
#define EX00_ADVCPP_BINARYSEARCHTREE_IMP_H

#include "BinarySearchTree.h"


template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &other) {
    root(other.root);
    size = other.size;
}

template<typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(const BinarySearchTree<T> &other) {
    if(this == &other) {
        return *this;
    }
    root.reset();
    root(other.root);
    size = other.size;
    return *this;
}

template<typename T>
std::shared_ptr<BstNode<T>> BinarySearchTree<T>::insert_rec(std::shared_ptr<BstNode<T>> node, T val) {
    if(node == nullptr) {
        return std::shared_ptr<BstNode<T>>(new BstNode<T>(val));
    }
    if(val < node->getData()) {
        node->setLeft(insert_rec(node->getLeft(), val));
        node->getLeft()->setParent(node);
    }
    else {
        node->setRight(insert_rec(node->getRight(), val));
        node->getRight()->setParent(node);
    }
    return node;
}

template<typename T>
void BinarySearchTree<T>::insert(T val) {
    size++;
    root = insert_rec(root, val);
}

template<typename T>
T* BinarySearchTree<T>::find_rec(std::shared_ptr<BstNode<T>> node, T val) {
    if(node==nullptr || size==0) {
        return nullptr;
    }
    if(val == node->getData()) {
        return root->getDataPointer();
    }
    else if(val < root->getData()) {
        return find_rec(node->getLeft(), val);
    }
    else {
        return find_rec(node->getRight(), val);
    }
}

template<typename T>
T* BinarySearchTree<T>::find(const T &element) {
    return find_rec(root, element);
}

template<typename T>
std::shared_ptr<BstNode<T>> BinarySearchTree<T>::remove_rec(std::shared_ptr<BstNode<T>> node, T val) {
    if(node == nullptr) {
        return nullptr;
    }
    if(val < node->getData()) {
        node->setLeft(remove_rec(node->getLeft(), val));
    }
    else if(val > node->getData()) {
        node->setRight(remove_rec(node->getRight(), val));
    }
    else {
        if(node->getLeft() == nullptr) {
            return node->getRight();
        }
        else if(node->getRight() == nullptr) {
            return node->getLeft();
        }
        node->setData(findMin(node->getRight())->getData());
        node->setRight(remove_rec(node->getRight(), node->getData()));
    }
    return node;
}

template<typename T>
void BinarySearchTree<T>::remove(const T &element) {
    if(!find(element)) {
        return;
    }
    size--;
    root = remove_rec(root, element);
}


template<typename T>
void BinarySearchTree<T>::Delete() {
    if(root == nullptr) {
        return;
    }
    while(root->getLeft() != nullptr) {
        remove(root->getLeft()->getData());
    }
    while(root->getRight() != nullptr) {
        remove(root->getRight()->getData());
    }
    remove(root->getData());
}

template<typename T>
T BinarySearchTree<T>::getHead() {
    return root->getData();
}

template<typename T>
void BinarySearchTree<T>::print_rec(std::shared_ptr<BstNode<T>> node) {
    if(node == nullptr) {
        return;
    }
    if(node->getLeft() != nullptr) {
        print_rec(node->getLeft());
    }
    std::cout << node->getData() << " ";
    if(node->getRight() != nullptr) {
        print_rec(node->getRight());
    }
}

template<typename T>
void BinarySearchTree<T>::print() {
    print_rec(root);
    std::cout << std::endl;
}

template<typename T>
std::shared_ptr<BstNode<T>> BinarySearchTree<T>::findMin(std::shared_ptr<BstNode<T>> node) {
    while(node->getLeft() != nullptr) {
        node = node->getLeft();
    }
    return node;
}


#endif //EX00_ADVCPP_BINARYSEARCHTREE_IMP_H
