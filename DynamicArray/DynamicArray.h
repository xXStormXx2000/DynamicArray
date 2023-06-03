
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
    DynamicArrayIterator operator+(long long a) {
        return mPtr + a;
    }
    DynamicArrayIterator& operator+=(long long a) {
        mPtr += a;
        return *this;
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
    DynamicArrayIterator operator-(long long a) {
        return mPtr - a;
    }
    DynamicArrayIterator& operator-=(long long a) {
        mPtr -= a;
        return *this;
    }
    valueType& operator[](size_t index) {
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
    DynamicArrayReverseIterator operator+(long long a) {
        return mPtr - a;
    }
    DynamicArrayReverseIterator& operator+=(long long a) {
        mPtr -= a;
        return *this;
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
    DynamicArrayReverseIterator operator-(long long a) {
        return mPtr + a;
    }
    DynamicArrayReverseIterator& operator-=(long long a) {
        mPtr += a;
        return *this;
    }
    valueType& operator[](size_t index) {
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
    // Space = O(1)
    DynamicArray() : mSize(0), mMemSize(0), mStart(0), mPtr(nullptr) {}
    //Constructor
    // Time = O(N)
    // Space = O(N)
    DynamicArray(size_t s) : mSize(s), mMemSize(s), mStart(0) {
        if (s < 0) throw std::invalid_argument("The size is negative");
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        memset(mPtr + mStart, 0, mSize * sizeof(T)); //copy operator is a b****
    }
    //Constructor
    // Time = O(N)
    // Space = O(N)
    DynamicArray(size_t s, const T& val) : mSize(s), mMemSize(s), mStart(0) {
        if (s < 0) throw std::invalid_argument("The size is negative");
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        memset(mPtr + mStart, 0, mSize * sizeof(T)); //copy operator is a b****
        for (size_t i = mStart; i < mStart + mSize; ++i) mPtr[i] = val;
    }
    //Copy constructor
    // Time = O(N)
    // Space = O(N)
    DynamicArray(const DynamicArray<T>& other) : mSize(other.mSize), mMemSize(other.mMemSize), mStart(other.mStart) {
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        memset(mPtr + mStart, 0, mSize * sizeof(T)); //copy operator is a b****
        for (size_t i = 0; i < mSize; ++i) mPtr[mStart + i] = other[i];
    }
    //Copy initializer list constructor
    // Time = O(N)
    // Space = O(N)
    DynamicArray(const std::initializer_list<T>& list) : mSize(list.size()), mMemSize(list.size()), mStart(0) {
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        int count = mStart;
        memset(mPtr + mStart, 0, mSize * sizeof(T)); //copy operator is a b****
        for (const T& i : list) {
            mPtr[count] = i;
            count++;
        }
    }
    //Move constructor
    // Time = O(1)
    // Space = O(1)
    DynamicArray(DynamicArray<T>&& other) noexcept : mSize(other.mSize), mMemSize(other.mMemSize), mStart(other.mStart) {
        mPtr = other.mPtr;
        memset(&other, 0, sizeof(DynamicArray<T>));
    }
    //Copy Operator
    // Time = O(N)
    // Space = O(N)
    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        if(&other == this) return *this;
        this->~DynamicArray();
        memcpy(this, &other, sizeof(DynamicArray<T>) - sizeof(T*));
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        memset(mPtr + mStart, 0, mSize * sizeof(T)); //copy operator is still a b****
        for (size_t i = 0; i < other.mSize; ++i) mPtr[mStart + i] = other[i];
        return *this;
    }
    //Copy Initializer list Operator
    // Time = O(N)
    // Space = O(N)
    DynamicArray<T>& operator = (const std::initializer_list<T>& list) {
        this->~DynamicArray();
        mSize = list.size();
        mMemSize = list.size();
        mStart = 0;
        mPtr = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        memset(mPtr + mStart, 0, mSize * sizeof(T)); //copy operator is still a b****
        size_t count = mStart;
        for (const T& i : list) {
            mPtr[count] = i;
            count++;
        }
        return *this;
    }
    //Move Operator
    // Time = O(N)
    // Space = O(1)
    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept {
        if (&other == this) return *this;
        this->~DynamicArray();
        memcpy(this, &other, sizeof(DynamicArray<T>));
        memset(&other, 0, sizeof(DynamicArray<T>));
        return *this;
    }
    // Time = O(N) * destructor of TYPE
    // Space = O(1)
    ~DynamicArray() {
        for (size_t i = 0; i < mSize; ++i) mPtr[mStart + i].~T();
        free(mPtr);
    }
    // Time = O(N) * comparatives operator of TYPE If sizes match O(1)
    // Space = O(1) * comparatives operator of TYPE
    bool operator==(const DynamicArray<T>& other) const {
        if (mSize != other.mSize) return false;
        for (size_t i = 0; i < mSize; ++i) if (mPtr[mStart + i] != other[i]) return false;
        return true;
    }
    // Time = O(1)
    // Space = O(1)
    T& operator[](size_t n) const {
        if (n >= mSize || n < 0) throw std::out_of_range("Out of range");
        return mPtr[mStart + n];
    }
    // Time = O(1)
    // Space = O(1)
    size_t size() const { return mSize; }
    // Time = O(N) If a resize is necessary else N(1), the is average is N(1) * copy operator of TYPE
    // Space = O(N) If a resize is necessary else N(1), the is average is N(1) * copy operator of TYPE
    void pushBack(const T& newElem) {
        if (mMemSize == mStart + mSize) {
            mMemSize += (mSize > 1 ? mSize : 1);
            T* temp = static_cast<T*>(realloc(mPtr, mMemSize * sizeof(T)));
            if (temp == NULL) throw std::runtime_error("Not enough memory");
            mPtr = temp;
        }
        mSize++;
        memset(mPtr + mStart + mSize - 1, 0, sizeof(T)); //copy operator is a b****
        mPtr[mStart + mSize - 1] = newElem;
    }
    // Time = O(N) If a resize is necessary else N(1), the is average is N(1) * copy operator of TYPE
    // Space = O(N) If a resize is necessary else N(1), the is average is N(1) * copy operator of TYPE
    void pushFront(const T& newElem) {
        if (0 == mStart) {
            mStart = (mSize > 1 ? mSize : 1);
            mMemSize += mStart;
            T* temp = static_cast<T*>(malloc(mMemSize * sizeof(T)));
            if (temp == NULL) throw std::runtime_error("Not enough memory");
            memcpy(temp + mStart, mPtr, mSize*sizeof(T));
            free(mPtr);
            mPtr = temp;
        }
        mStart--;
        mSize++;
        memset(mPtr + mStart, 0, sizeof(T)); //copy operator is a b****
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
        return std::move(mPtr[mStart + mSize]);
    }
    // Time = O(1)
    // Space = O(1)
    T front() const { return mPtr[mStart]; }
    // Time = O(1)
    // Space = O(1)
    T popFront() {
        if (mSize == 0) throw std::logic_error("Tried to pop front on empty DynamicArray");
        mStart++;
        mSize--;
        return std::move(mPtr[mStart - 1]);
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
    // Time = O(N*log(N)) * (function + copy operator of TYPE)
    // Space = O(N) * (function + copy operator of TYPE)
    void sort(size_t start, size_t end, bool (*function)(const T&, const T&)) {
        if (start > end) throw std::invalid_argument("Start is past End");
        if (start == end - 1 || start == end) return;
        size_t mid = (start + end) >> 1;
        sort(start, mid, function);
        sort(mid, end, function);
        DynamicArray temp(end - start);
        size_t start1 = start;
        size_t start2 = mid;
        for (size_t i = 0; i < temp.size(); ++i) {
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
        for (size_t i = 0; i < temp.size(); ++i) mPtr[mStart + start + i] = temp[i];
    }
    // sort(start inclusive, end exclusive)
    // Time = O(N*log(N)) * copy operator of TYPE
    // Space = O(N) * copy operator of TYPE
    void sort(size_t start, size_t end) {
        this->sort(start, end, [](const T& a, const T& b) { return a < b; });
    }
    // Time = O(N*log(N)) * copy operator of TYPE
    // Space = O(N) * copy operator of TYPE
    void sort() {
        this->sort(0, mSize);
    }
    // find(Iterator first, Iterator last, const T& val, bool function pointer)
    // Time = O(N) * function
    // Space = O(1) * function
    template <typename InputIterator>
    InputIterator find(InputIterator first, InputIterator last, const T& val, bool (*function)(const T&, const T&)) {
        while (first != last) {
            if (function(*first, val)) return first;
            ++first;
        }
        return last;
    }
    // find(Iterator first, Iterator last, const T& val)
    // Time = O(N)
    // Space = O(1)
    template <typename InputIterator>
    InputIterator find(InputIterator first, InputIterator last, const T& val) {
        return find(first, last, val, [](const T& a, const T& b) { return a == b; });
    }
    // find(const T& val)
    // Time = O(N)
    // Space = O(1)
    Iterator find(const T& val) {
        return find(this->begin(), this->end(), val);
    }
    // Time = O(N) I want to die
    // Space = O(N) Please
    void shrinkToFit() {
        mMemSize = mSize;
        T* temp = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        if (temp == NULL) throw std::runtime_error("Not enough memory");
        memcpy(temp, mPtr + mStart, mSize * sizeof(T));
        mStart = 0;
        free(mPtr);
        mPtr = temp;
    }
    // Time = O(N) I want to die
    // Space = O(N) Please
    void shrinkToFitFront() {
        mMemSize -= mStart;
        T* temp = static_cast<T*>(malloc(mMemSize * sizeof(T)));
        if (temp == NULL) throw std::runtime_error("Not enough memory");
        memcpy(temp, mPtr + mStart, mSize * sizeof(T));
        mStart = 0;
        free(mPtr);
        mPtr = temp;
    }
    // Time = O(1)
    // Space = O(1)
    void shrinkToFitBack() {
        mMemSize = mSize + mStart;
        T* temp = static_cast<T*>(realloc(mPtr, mMemSize * sizeof(T)));
        if (temp == NULL) throw std::runtime_error("Not enough memory");
        mPtr = temp;
    }
private:
    size_t mSize;
    size_t mStart;
    size_t mMemSize;
    T* mPtr;
};
