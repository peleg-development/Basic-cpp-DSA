#include <iostream>
#include <stdexcept>

using namespace std;

/*
Challenge 3: std::vector

What is std::vector?
- A sequence container that stores elements contiguously in memory.
- Similar to a dynamic array, it can grow or shrink as needed.

Built with:
- A dynamically-allocated array that doubles its size when capacity is exceeded.
- Provides O(1) random access to elements by index.

Common operations:
- push_back(value): Insert at the end. Amortized O(1)
- operator[](index): Access element at given index. O(1)
- at(index): Bounds-checked access. O(1)
- size(): Returns the number of elements. O(1)
- insert/erase in the middle: O(n), since elements must be shifted.

By working on this challenge, you will understand how vectors provide fast random access
and are efficient for sequential insertions/deletions at the end.
*/

template<typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t length;

    void resize(int new_size) {
        T* new_data;
        for (int i = 0; i < capacity; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_size;

        if (length > capacity) {
            length = capacity;
        }
    }

public:
    Vector(size_t& capacity) {
        this->capacity = capacity;
        this->length = 0;
        data = new T[capacity];
    }

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (capacity == length) {
            resize(capacity * 2);
        }
        data[length++] = value;
    }

    T& operator[](const size_t& index) const {
        return data[index];
    }

    T& at(const size_t& index) const {
        if (index >= length) {
            throw out_of_range("Cannot access uncreated element");
        }
        return data[index];
    }

    size_t size() const {
        return length;
    }

    T& pop_back() {
        T old_last = data[length - 1];
        data[length - 1] = T();
        length--;
        return old_last;
    }

    void clear() {
        for (int i = 0; i < length; ++i) {
            data[i] = T();
        }
        length = 0;
    }

    size_t find(const T& value) {
        for (int i = 0; i < length; ++i) {
            if (value == data[i]) {
                return i;
            }
        }
        return SIZE_MAX;
    }

    void erase(size_t start, size_t end = SIZE_MAX) {
        if (end == SIZE_MAX) {
            end = start + 1;
        }

        if (start >= length || end > length || start >= end) {
            throw out_of_range("Invalid range");
        }

        size_t range = end - start;

        for (size_t i = end; i < length; ++i) {
            data[i - range] = data[i];
        }

        length -= range;
    }

    T* begin() { return data; }
    T* end() { return data + length; }
    const T* begin() const { return data; }
    const T* end() const { return data + length; }

};

