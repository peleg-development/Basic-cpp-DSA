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

class Vector {
private:
    int* data;        // Pointer to the array that holds elements
    size_t capacity;  // Total allocated capacity of the vector
    size_t length;    // Current number of elements in the vector

    /**
     * Helper function to resize the internal array when it runs out of capacity.
     * Ensures efficient storage expansion.
     */
    void resize();

public:
    /**
     * Default constructor:
     * Initializes an empty vector with a default capacity.
     */
    Vector();

    /**
     * Destructor:
     * Cleans up dynamically allocated memory when the vector is destroyed.
     */
    ~Vector();

    /**
     * Add a new element to the end of the vector.
     * Expands the capacity if necessary.
     */
    void push_back(int value);

    /**
     * Access an element by index (non-bounds-checked).
     * Returns a reference to the element for modification.
     */
    int& operator[](size_t index);

    /**
     * Access an element by index with bounds checking.
     * Throws an exception if the index is out of range.
     */
    int& at(size_t index);

    /**
     * Returns the number of elements in the vector.
     */
    size_t size() const;

    /**
     * Removes the last element of the vector.
     * Does nothing if the vector is already empty.
     */
    void pop_back();

    /**
     * Clears all elements in the vector without deallocating memory.
     */
    void clear();
};


void vect_test() {

}