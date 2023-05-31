
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
    bool operator==(const DynamicArrayIterator& other) const {
        return mPtr == other.mPtr;
    }
    bool operator!=(const DynamicArrayIterator& other) const {
        return mPtr != other.mPtr;
    }
};

template<typename dArray>
class DynamicArrayReverseIterator {
public:
    using valueType = typename dArray::valueType;
private:
    valueType* mPtr;
public:
    DynamicArrayReverseIterator(valueType* ptr) : mPtr(ptr) {}
    DynamicArrayReverseIterator& operator++() {
        mPtr--;
        return *this;
    }
    DynamicArrayReverseIterator operator++(int) {
        DynamicArrayReverseIterator it = *this;
        ++(*this);
        return it;
    }
    DynamicArrayReverseIterator& operator--() {
        mPtr++;
        return *this;
    }
    DynamicArrayReverseIterator operator--(int) {
        DynamicArrayReverseIterator it = *this;
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
    bool operator==(const DynamicArrayReverseIterator& other) const {
        return mPtr == other.mPtr;
    }
    bool operator!=(const DynamicArrayReverseIterator& other) const {
        return mPtr != other.mPtr;
    }
};

template<typename T>
class DynamicArray {
public:
    using valueType = T;
    using Iterator = DynamicArrayIterator<DynamicArray<T>>;
    using ReverseIterator = DynamicArrayReverseIterator<DynamicArray<T>>;
    //Constructor
    // Time = O(1)
    // Space = O(N)
    DynamicArray(int s = 0) : mSize(s), mMemSize(s + 2), mStart(1) {
        if (s < 0) throw std::invalid_argument("The size is negative");
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
    }
    //Constructor
    // Time = O(N)
    // Space = O(N)
    DynamicArray(int s, const T& val) : mSize(s), mMemSize(s + 2), mStart(1) {
        if (s < 0) throw std::invalid_argument("The size is negative");
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        for (int i = mStart; i < mStart + mSize; i++) mPtr[i] = val;
    }
    //Copy constructor
    // Time = O(N)
    // Space = O(N)
    DynamicArray(const DynamicArray<T>& other) : mSize(other.mSize), mMemSize(other.mMemSize), mStart(other.mStart) {
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        for (int i = 0; i < other.mSize; i++) mPtr[mStart + i] = other[i];
    }
    //Copy initializer list constructor
    // Time = O(N)
    // Space = O(N)
    DynamicArray(const std::initializer_list<T>& list) : mSize(list.size()), mMemSize(list.size() + 1), mStart(0) {
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        int count = mStart;
        for (T i : list) {
            mPtr[count] = i;
            count++;
        }
    }
    //Move constructor
    // Time = O(1)
    // Space = O(1)
    DynamicArray(DynamicArray<T>&& other) noexcept : mSize(other.mSize), mMemSize(other.mMemSize), mStart(other.mStart) {
        mPtr = other.mPtr;
        other.mPtr = nullptr;
        other.mSize = 0;
        other.mMemSize = 0;
        other.mStart = 0;
    }
    //Copy Operator
    // Time = O(N)
    // Space = O(N)
    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        if(&other == this) return *this;
        mSize = other.mSize;
        mMemSize = other.mMemSize;
        mStart = other.mStart;
        free(mPtr);
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        for (int i = 0; i < other.mSize; i++) mPtr[mStart + i] = other[i];
        return *this;
    }
    //Copy Initializer list Operator
    // Time = O(N)
    // Space = O(N)
    DynamicArray<T>& operator = (const std::initializer_list<T>& list) {
        mSize = list.size();
        mMemSize = list.size() + 2;
        mStart = 1;
        free(mPtr);
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        int count = mStart;
        for (T i : list) {
            mPtr[count] = i;
            count++;
        }
        return *this;
    }
    //Move Operator
    // Time = O(1)
    // Space = O(1)
    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept {
        if (&other == this) return *this;
        mSize = other.mSize;
        mMemSize = other.mMemSize;
        mStart = other.mStart;
        free(mPtr);
        mPtr = other.mPtr;
        other.mPtr = nullptr;
        other.mSize = 0;
        other.mMemSize = 0;
        other.mStart = 0;
        return *this;
    }
    // Time = O(1)
    // Space = O(1)
    ~DynamicArray() {
        for (int i = 0; i < mSize; ++i) (mPtr + mStart + i)->~T();
        free(mPtr);
    }
    // Time = O(N) If the sizes match else O(1)
    // Space = O(1)
    bool operator==(const DynamicArray<T>& other) const {
        if (mSize != other.mSize) return false;
        for (int i = 0; i < mSize; ++i) if (mPtr[mStart + i] != other[i]) return false;
        return true;
    }
    // Time = O(1)
    // Space = O(1)
    T& operator[](int n) const {
        if (n >= mSize || n < 0) throw std::out_of_range("Out of range");
        return mPtr[mStart + n];
    }
    // Time = O(1)
    // Space = O(1)
    size_t size() const { return mSize; }
    // Time = O(N) If a resize is necessary else N(1), the is average is N(1)
    // Space = O(N) If a resize is necessary else N(1), the is average is N(1)
    void pushBack(const T& newElem) {
        if (mMemSize == mStart + mSize) {
            mMemSize += mSize;
            T* temp = static_cast<T*>(realloc(mPtr, mMemSize * sizeof(T)));
            if (temp == NULL) throw std::runtime_error("Not enough memory");
            mPtr = temp;
        }
        mSize++;
        memset(mPtr + mStart + mSize - 1, 0, sizeof(T));
        mPtr[mStart + mSize - 1] = newElem;
    }
    // Time = O(N) If a resize is necessary else N(1), the is average is N(1)
    // Space = O(N) If a resize is necessary else N(1), the is average is N(1)
    void pushFront(const T& newElem) {
        if (0 == mStart) {
            mStart = mSize;
            mMemSize += mStart;
            T* temp = static_cast<T*>(malloc(mMemSize * sizeof(T)));
            if (temp == NULL) throw std::runtime_error("Not enough memory");
            memcpy(temp + mStart, mPtr, mSize*sizeof(T));
            free(mPtr);
            mPtr = temp;
        }
        mStart--;
        mSize++;
        memset(mPtr + mStart, 0, sizeof(T));
        mPtr[mStart] = newElem;
    }
    // Time = O(1)
    // Space = O(1)
    T back() const { return mPtr[mStart + mSize - 1]; }
    // Time = O(1)
    // Space = O(1)
    T popBack() {
        if (mSize == 0) throw std::logic_error("Tried to pop back on empty DynamicArray");
        mSize--;
        return mPtr[mStart + mSize];
    }
    // Time = O(1)
    // Space = O(1)
    T popFront() {
        if (mSize == 0) throw std::logic_error("Tried to pop front on empty DynamicArray");
        mStart++;
        mSize--;
        return mPtr[mStart - 1];
    }
    // Time = O(1)
    // Space = O(1)
    Iterator begin() const {
        return Iterator(mPtr + mStart);
    }
    // Time = O(1)
    // Space = O(1)
    Iterator end() const {
        return Iterator(mPtr + mStart + mSize);
    }
    // Time = O(1)
    // Space = O(1)
    ReverseIterator rBegin() const {
        return ReverseIterator(mPtr + mStart + mSize - 1);
    }
    // Time = O(1)
    // Space = O(1)
    ReverseIterator rEnd() const {
        return ReverseIterator(mPtr + mStart - 1);
    }
    // sort(start inclusive, end exclusive, bool function pointer)
    // Time = O(N*log(N))
    // Space = O(N)
    void sort(int start, int end, bool (*function)(const T&, const T&)) {
        if (start > end) throw std::invalid_argument("Start is past End");
        if (start == end - 1 || start == end) return;
        int mid = (start + end) >> 1;
        sort(start, mid, function);
        sort(mid, end, function);
        DynamicArray temp(end - start);
        int start1 = start;
        int start2 = mid;
        for (int i = 0; i < temp.size(); i++) {
            if (start1 == mid) {
                temp[i] = mPtr[mStart + start2];
                start2++;
                continue;
            }
            if (start2 == end) {
                temp[i] = mPtr[mStart + start1];
                start1++;
                continue;
            }
            if (function(mPtr[mStart + start1], mPtr[mStart + start2])) {
                temp[i] = mPtr[mStart + start1];
                start1++;
            } else {
                temp[i] = mPtr[mStart + start2];
                start2++;
            }
        }
        for (int i = 0; i < temp.size(); i++) mPtr[mStart + start + i] = temp[i];
    }
    // sort(start inclusive, end exclusive)
    // Time = O(N*log(N))
    // Space = O(N)
    void sort(int start, int end) {
        this->sort(start, end, [](const T& a, const T& b) { return a < b; });
    }
    // Time = O(N*log(N))
    // Space = O(N)
    void sort() {
        this->sort(0, mSize);
    }
private:
    T* mPtr;
    size_t mSize;
    size_t mStart;
    size_t mMemSize;
};