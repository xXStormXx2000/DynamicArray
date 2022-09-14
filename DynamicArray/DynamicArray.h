#pragma once
#include <stdexcept>
template<class T>
class DynamicArray {
private:
    T* c;
    int siz;
    int memSize;
public:
    DynamicArray(int s = 0);
    DynamicArray(const DynamicArray<T>& other);
    DynamicArray<T>& operator = (const DynamicArray<T>&);
    ~DynamicArray();
    bool operator==(const DynamicArray<T>&);
    T& operator[](int);
    int size();
    void pushBack(T);
    T back() const;
    T popBack();
};

template<class T>
DynamicArray<T>::DynamicArray(int s) : siz(s), memSize(s + 1) {
    if (s < 0) throw std::invalid_argument("The size is negative");
    c = static_cast<T*>(malloc(memSize * sizeof(T)));
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) : siz(other.siz), memSize(other.memSize) {
    c = static_cast<T*>(malloc(memSize * sizeof(T)));
    for (int i = 0; i < other.siz; i++) c[i] = other.c[i];
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    siz = other.siz;
    memSize = other.memSize;
    c = static_cast<T*>(malloc(memSize * sizeof(T)));
    for (int i = 0; i < other.siz; i++) c[i] = other.c[i];
    return *this;
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    free(c);
}

template<class T>
bool DynamicArray<T>::operator==(const DynamicArray<T>& other) {
    if (siz != other.siz) return false;
    for (int i = 0; i < siz; i++) if (c[i] != other.c[i]) return false;
    return true;
}

template<class T>
T& DynamicArray<T>::operator[](int n) {
    if (n >= siz || n < 0) throw std::out_of_range("Out of range");
    return c[n];
}

template<class T>
int DynamicArray<T>::size() { return siz; }

template<class T>
void DynamicArray<T>::pushBack(T newElem) {
    if (memSize == siz) {
        memSize = memSize * 2;
        T* temp = static_cast<T*>(realloc(c, memSize * sizeof(T)));
        if (temp != NULL) c = temp;
    }
    siz++;
    c[siz - 1] = newElem;
}

template<class T>
T DynamicArray<T>::back() const { return c[siz - 1]; }

template<class T>
T DynamicArray<T>::popBack() {
    siz--;
    if (memSize > siz * 4) {
        memSize = (memSize >> 1) + 1;
        c = static_cast<T*>(realloc(c, memSize * sizeof(T)));
    }
    return c[siz];
}