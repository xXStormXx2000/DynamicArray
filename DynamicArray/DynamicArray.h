#pragma once
#include <stdexcept>
#include <initializer_list>
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
    DynamicArray(int s = 0);
    DynamicArray(const DynamicArray<T>&);
    DynamicArray(std::initializer_list<T>);
    DynamicArray<T>& operator = (const DynamicArray<T>&);
    DynamicArray<T>& operator = (std::initializer_list<T>);
    ~DynamicArray();
    bool operator==(const DynamicArray<T>&);
    T& operator[](int);
    int size();
    void pushBack(T);
    T back() const;
    T popBack();
    Iterator begin();
    Iterator end();
};

template<typename T>
DynamicArray<T>::DynamicArray(int s) : siz(s), memSize(s + 1) {
    if (s < 0) throw std::invalid_argument("The size is negative");
    c = static_cast<T*>(malloc(memSize * sizeof(T)));
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) : siz(other.siz), memSize(other.memSize) {
    c = static_cast<T*>(malloc(memSize * sizeof(T)));
    for (int i = 0; i < other.siz; i++) c[i] = other.c[i];
}

template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> list) : siz(list.size()), memSize(list.size() + 1) {
    c = static_cast<T*>(malloc(memSize * sizeof(T)));
    int count = 0;
    for (T i : list) {
        c[count] = i;
        count++;
    }
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    siz = other.siz;
    memSize = other.memSize;
    c = static_cast<T*>(malloc(memSize * sizeof(T)));
    for (int i = 0; i < other.siz; i++) c[i] = other.c[i];
    return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(std::initializer_list<T> list) {
    siz = list.size();
    memSize = list.size() + 1;
    c = static_cast<T*>(malloc(memSize * sizeof(T)));
    int count = 0;
    for (T i : list) {
        c[count] = i;
        count++;
    }
    return *this;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    free(c);
}

template<typename T>
bool DynamicArray<T>::operator==(const DynamicArray<T>& other) {
    if (siz != other.siz) return false;
    for (int i = 0; i < siz; i++) if (c[i] != other.c[i]) return false;
    return true;
}

template<typename T>
T& DynamicArray<T>::operator[](int n) {
    if (n >= siz || n < 0) throw std::out_of_range("Out of range");
    return c[n];
}

template<typename T>
int DynamicArray<T>::size() { return siz; }

template<typename T>
void DynamicArray<T>::pushBack(T newElem) {
    if (memSize == siz) {
        memSize *= 2;
        T* temp = static_cast<T*>(realloc(c, memSize * sizeof(T)));
        if (temp != NULL) c = temp;
    }
    siz++;
    c[siz - 1] = newElem;
}

template<typename T>
T DynamicArray<T>::back() const { return c[siz - 1]; }

template<typename T>
T DynamicArray<T>::popBack() {
    siz--;
    if (memSize > siz * 4) {
        memSize = (memSize >> 1) + 1;
        c = static_cast<T*>(realloc(c, memSize * sizeof(T)));
    }
    return c[siz];
}

template<typename T>
DynamicArrayIterator<DynamicArray<T>> DynamicArray<T>::begin() {
    return Iterator(c);
}

template<typename T>
DynamicArrayIterator<DynamicArray<T>> DynamicArray<T>::end() {
    return Iterator(c + siz);
}
