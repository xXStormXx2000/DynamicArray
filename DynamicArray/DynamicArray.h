#pragma once
#include <stdexcept>
#include <initializer_list>
#include <iostream>

template<typename dArray>
class DynamicArrayIterator {
public:
    using valueType = typename dArray::valueType;
private:
    valueType* mPtr;
public:
    DynamicArrayIterator(valueType* ptr) : mPtr(ptr) {}
    DynamicArrayIterator& operator++() {
        mPtr++;
        return *this;
    }
    DynamicArrayIterator operator++(int) {
        DynamicArrayIterator it = *this;
        ++(*this);
        return it;
    }
    DynamicArrayIterator& operator--() {
        mPtr--;
        return *this;
    }
    DynamicArrayIterator operator--(int) {
        DynamicArrayIterator it = *this;
        --(*this);
        return it;
    }
    valueType& operator[](int index) {
        return *(mPtr[index]);
    }
    valueType* operator->() {
        return mPtr;
    }
    valueType& operator*() {
        return *mPtr;
    }
    bool operator==(const DynamicArrayIterator& other) {
        return mPtr == other.mPtr;
    }
    bool operator!=(const DynamicArrayIterator& other) {
        return mPtr != other.mPtr;
    }
};

template<typename T>
class DynamicArray {
public:
    using valueType = T;
    using Iterator = DynamicArrayIterator<DynamicArray<T>>;
private:
    T* c;
    int siz;
    int memSize;
public:
    //Constructor
    DynamicArray(int s = 0) : siz(s), memSize(s + 1) {
        if (s < 0) throw std::invalid_argument("The size is negative");
        c = static_cast<T*>(malloc(memSize * sizeof(T)));
    }
    //Constructor
    DynamicArray(int s, const T& val) : siz(s), memSize(s + 1) {
        if (s < 0) throw std::invalid_argument("The size is negative");
        c = static_cast<T*>(malloc(memSize * sizeof(T)));
        for (int i = 0; i < siz; i++) c[i] = val;
    }
    //Copy Constructor
    DynamicArray(const DynamicArray<T>& other) : siz(other.siz), memSize(other.memSize) {
        c = static_cast<T*>(malloc(memSize * sizeof(T)));
        for (int i = 0; i < other.siz; i++) c[i] = other.c[i];
    }
    //Copy initializer list Constructor
    DynamicArray(const std::initializer_list<T>& list) : siz(list.size()), memSize(list.size() + 1) {
        c = static_cast<T*>(malloc(memSize * sizeof(T)));
        int count = 0;
        for (T i : list) {
            c[count] = i;
            count++;
        }
    }
    //Move Constructor
    DynamicArray(DynamicArray<T>&& other) : siz(other.siz), memSize(other.memSize) {
        c = other.c;
        other.c = nullptr;
        other.siz = 0;
        other.memSize = 0;
    }
    //Copy Operator
    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        siz = other.siz;
        memSize = other.memSize;
        free(c);
        c = static_cast<T*>(malloc(memSize * sizeof(T)));
        for (int i = 0; i < other.siz; i++) c[i] = other.c[i];
        return *this;
    }
    //Copy Initializer list Operator
    DynamicArray<T>& operator = (const std::initializer_list<T>& list) {
        siz = list.size();
        memSize = list.size() + 1;
        free(c);
        c = static_cast<T*>(malloc(memSize * sizeof(T)));
        int count = 0;
        for (T i : list) {
            c[count] = i;
            count++;
        }
        return *this;
    }

    //Move Operator
    DynamicArray<T>& operator=(DynamicArray<T>&& other) {
        siz = other.siz;
        memSize = other.memSize;
        free(c);
        c = other.c;
        other.c = nullptr;
        other.siz = 0;
        other.memSize = 0;
        return *this;
    }

    ~DynamicArray() {
        free(c);
    }
    bool operator==(const DynamicArray<T>& other) {
        if (siz != other.siz) return false;
        for (int i = 0; i < siz; i++) if (c[i] != other.c[i]) return false;
        return true;
    }
    T& operator[](int n) {
        if (n >= siz || n < 0) throw std::out_of_range("Out of range");
        return c[n];
    }
    int size() { return siz; }
    void pushBack(T newElem) {
        if (memSize == siz) {
            memSize *= 2;
            T* temp = static_cast<T*>(realloc(c, memSize * sizeof(T)));
            if (temp != NULL) c = temp;
        }
        siz++;
        c[siz - 1] = newElem;
    }
    T back() const { return c[siz - 1]; }
    T popBack() {
        siz--;
        if (memSize > siz * 4) {
            memSize = (memSize >> 1) + 1;
            c = static_cast<T*>(realloc(c, memSize * sizeof(T)));
        }
        return c[siz];
    }
    Iterator begin() {
        return Iterator(c);
    }
    Iterator end() {
        return Iterator(c + siz);
    }
};
