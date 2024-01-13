#ifndef EX00_ADVCPP_ITERATOR_IMP_H
#define EX00_ADVCPP_ITERATOR_IMP_H

#include "MyVector.h"
template<typename T>
typename MyVector<T>::iterator &MyVector<T>::iterator::operator=(const MyVector::iterator &other) {
    if(this == &other) {
        return *this;
    }
    ptr = other.ptr;
    return *this;
}

template<typename T>
bool MyVector<T>::iterator::operator==(const MyVector::iterator &other) {
    return ptr == other.ptr;
}

template<typename T>
bool MyVector<T>::iterator::operator!=(const MyVector::iterator &other) {
    return ptr != other.ptr;
}

template<typename T>
bool MyVector<T>::iterator::operator<(const MyVector::iterator &other) {
    return ptr < other.ptr;
}

template<typename T>
bool MyVector<T>::iterator::operator<=(const MyVector::iterator &other) {
    return ptr <= other.ptr;
}

template<typename T>
bool MyVector<T>::iterator::operator>(const MyVector::iterator &other) {
    return ptr > other.ptr;
}

template<typename T>
bool MyVector<T>::iterator::operator>=(const MyVector::iterator &other) {
    return ptr >= other.ptr;
}

template<typename T>
typename MyVector<T>::iterator &MyVector<T>::iterator::operator++() {
    ++ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator++(int) {
    ptr++;
    return *this;
}

template<typename T>
typename MyVector<T>::iterator &MyVector<T>::iterator::operator--() {
    --ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator--(int) {
    ptr--;
    return *this;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator+(std::ptrdiff_t pd) const {
    return iterator(ptr + pd);
}

template<typename T>
typename MyVector<T>::iterator &MyVector<T>::iterator::operator+=(std::ptrdiff_t pd) {
    ptr += pd;
    return *this;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator-(std::ptrdiff_t pd) const {
    return iterator(ptr - pd);
}

template<typename T>
typename MyVector<T>::iterator &MyVector<T>::iterator::operator-=(std::ptrdiff_t pd) {
    ptr -= pd;
    return *this;
}

template<typename T>
T &MyVector<T>::iterator::operator*() const {
    return *ptr;
}

template<typename T>
T &MyVector<T>::iterator::operator->() const {
    return ptr;
}

template<typename T>
T &MyVector<T>::iterator::operator[](std::ptrdiff_t pd) const {
    return *(ptr + pd);
}


#endif //EX00_ADVCPP_ITERATOR_IMP_H
