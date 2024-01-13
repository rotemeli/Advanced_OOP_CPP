#ifndef EX00_ADVCPP_BSTNODE_H
#define EX00_ADVCPP_BSTNODE_H

#include <iostream>
#include <memory>

template<typename T>
class BstNode {
private:
    T data;
    std::shared_ptr<BstNode<T>> parent;
    std::shared_ptr<BstNode<T>> left;
    std::shared_ptr<BstNode<T>> right;

public:
    // Constructors
    BstNode() = delete;
    explicit BstNode(T element) : data(element), parent(nullptr), left(nullptr), right(nullptr) {}

    // Getters
    T getData() const {
        return data;
    }

    const std::shared_ptr<BstNode<T>> &getParent() const {
        return parent;
    }

    const std::shared_ptr<BstNode<T>> &getLeft() const {
        return left;
    }

    const std::shared_ptr<BstNode<T>> &getRight() const {
        return right;
    }

    T* getDataPointer() {
        return &data;
    }

    // Setters
    void setData(T d) {
        BstNode::data = d;
    }

    void setParent(const std::shared_ptr<BstNode<T>> &p) {
        BstNode::parent = p;
    }

    void setLeft(const std::shared_ptr<BstNode<T>> &l) {
        BstNode::left = l;
    }

    void setRight(const std::shared_ptr<BstNode<T>> &r) {
        BstNode::right = r;
    }
};


#endif //EX00_ADVCPP_BSTNODE_H
