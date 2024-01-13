#ifndef EX00_ADVCPP_MYVECTOR_IMP_H
#define EX00_ADVCPP_MYVECTOR_IMP_H

#include "MyVector.h"

template<typename T>
MyVector<T>::MyVector() {
    arr = std::shared_ptr<T[]>(new T[10]);
    max_size = 10;
    curr_size = 0;
}

template<typename T>
MyVector<T>::MyVector(int size) {
    arr = std::shared_ptr<T[]>(new T[size]);
    max_size = size;
    curr_size = size;
    for(int i = 0; i < size; i++) {
        arr[i] = T();
    }
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T> &other) {
    arr = std::shared_ptr<T[]>(new T[other.max_size]);
    for(int i = 0; i < other.curr_size; i++) {
        arr[i] = other.arr[i];
    }
    max_size = other.max_size;
    curr_size = other.curr_size;
}

template<typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &other) {
    if(this == &other) {
        return *this;
    }
    arr.reset();
    arr = std::shared_ptr<T[]>(new T[other.max_size]);
    for(int i = 0; i < other.curr_size; i++) {
        arr[i] = other.arr[i];
    }
    max_size = other.max_size;
    curr_size = other.curr_size;
    return *this;
}

template<typename T>
MyVector<T>::MyVector(MyVector<T> &&rhs) noexcept {
    arr = rhs.arr;
    max_size = rhs.max_size;
    curr_size = rhs.curr_size;
    rhs.arr.reset();
    rhs.curr_size = 0;
    rhs.max_size = 0;
}

template<typename T>
MyVector<T> &MyVector<T>::operator=(MyVector<T> &&rhs) noexcept {
    if(this == &rhs) {
        return *this;
    }
    arr = rhs.arr;
    max_size = rhs.max_size;
    curr_size = rhs.curr_size;
    rhs.arr.reset();
    rhs.curr_size = 0;
    rhs.max_size = 0;
    return *this;
}

template<typename T>
void MyVector<T>::push_back(T element) {
    if(curr_size == max_size) {
        std::shared_ptr<T[]> tmp = arr;
        arr.reset(new T[max_size * 2]);
        for(int i = 0; i < curr_size; i++) {
            arr[i] = tmp[i];
        }
    }
    arr[curr_size++] = element;
}

template<typename T>
void MyVector<T>::pop_back() {
    if(curr_size == 0) {
        throw std::invalid_argument("Vector is empty!\n");
    }
    curr_size--;
}

template<typename T>
T &MyVector<T>::operator[](int index) {
    if(index < 0 || index > curr_size-1) {
        throw std::invalid_argument("Invalid argument!\n");
    }
    return arr[index];
}

template<typename T>
const T &MyVector<T>::operator[](int index) const {
    if(index < 0 || index > curr_size-1) {
        throw std::invalid_argument("\nInvalid index!\n");
    }
    return arr[index];
}

template<typename T>
void MyVector<T>::clear() {
    curr_size = 0;
}

template<typename T>
void MyVector<T>::resize(int new_size) {
    if(new_size <= curr_size) {
        curr_size = new_size;
    }
    else {
        max_size = new_size;
        std::shared_ptr<T[]> tmp = arr;
        arr.reset(new T[new_size]);
        int i;
        for(i = 0; i < curr_size; i++) {
            arr[i] = tmp[i];
        }
        for(; i < max_size; i++) {
            arr[i] = T();
        }
        curr_size = max_size;
        tmp.reset();
    }
}

template<typename T> template<class Comp>
void MyVector<T>::sort(Comp cmp) {
    for(int i = 0; i < curr_size-1; i++) {
        for(int j = i + 1; j < curr_size; j++) {
            if(cmp(arr[j], arr[i])) {
                T tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::begin() {
    return iterator(arr.get());
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::end() {
    return iterator(arr.get() + curr_size);
}

#endif //EX00_ADVCPP_MYVECTOR_IMP_H
