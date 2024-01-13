#ifndef EX00_ADVCPP_BINARYSEARCHTREE_H
#define EX00_ADVCPP_BINARYSEARCHTREE_H

#include <iostream>
#include <memory>

#include "BstNode.h"

template<typename T>
class BinarySearchTree {
private:
    std::shared_ptr<BstNode<T>> root;
    int size;

    std::shared_ptr<BstNode<T>> insert_rec(std::shared_ptr<BstNode<T>> node, T val);
    T* find_rec(std::shared_ptr<BstNode<T>>, T val);
    std::shared_ptr<BstNode<T>> findMin(std::shared_ptr<BstNode<T>>);
    std::shared_ptr<BstNode<T>> remove_rec(std::shared_ptr<BstNode<T>> node, T val);
    void print_rec(std::shared_ptr<BstNode<T>> node);

public:
    BinarySearchTree() : root(nullptr), size(0) {}

    /*
     * Big three
     */
    BinarySearchTree(const BinarySearchTree<T>& other);
    BinarySearchTree& operator=(const BinarySearchTree<T>& other);
    ~BinarySearchTree() = default;

    // Methods
    void insert(T val);
    T* find(const T& element);
    void remove(const T& element);
    void Delete();
    T getHead();
    void print();                   // InOrder print

};

#include "BinarySearchTree_imp.h"

#endif //EX00_ADVCPP_BINARYSEARCHTREE_H
