#ifndef EX00_ADVCPP_MYVECTOR_H
#define EX00_ADVCPP_MYVECTOR_H

#include <iostream>
#include <memory>


template <typename T>
class MyVector {
private:
    std::shared_ptr<T[]> arr;
    int max_size;
    int curr_size;

public:
    class iterator {
    private:
        T* ptr;

    public:
        iterator() : ptr(nullptr) {}
        explicit iterator(T* p) : ptr(p) {}
        /*
         * Big three
         */
        iterator(const iterator& other) : ptr(other.ptr) {}
        iterator& operator=(const iterator& other);
        ~iterator() = default;

        // Boolean operators
        bool operator==(const iterator& other);
        bool operator!=(const iterator& other);
        bool operator<(const iterator& other);
        bool operator<=(const iterator& other);
        bool operator>(const iterator& other);
        bool operator>=(const iterator& other);

        // Other operators
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator operator+(std::ptrdiff_t pd) const;
        iterator& operator+=(std::ptrdiff_t pd);
        iterator operator-(std::ptrdiff_t pd) const;
        iterator& operator-=(std::ptrdiff_t pd);
        T& operator*() const;
        T& operator->() const;
        T& operator[](std::ptrdiff_t pd) const;
    };

    MyVector();
    explicit MyVector(int size);

    /*
     * Big five
     */
    MyVector(const MyVector<T>& other);
    MyVector<T>& operator=(const MyVector<T>& other);
    ~MyVector() = default;
    MyVector(MyVector<T>&& rhs) noexcept;
    MyVector<T>& operator=(MyVector<T>&& rhs) noexcept;

    void push_back(T element);
    void pop_back();
    T& operator[](int index);                       // Read only access
    const T& operator[](int index) const;           // Write access
    void clear();
    void resize(int new_size);

    template<class Comp>
    void sort(Comp cmp);

    iterator begin();
    iterator end();

};

#include "MyVector_imp.h"
#include "iterator_imp.h"

#endif //EX00_ADVCPP_MYVECTOR_H
