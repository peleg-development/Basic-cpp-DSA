#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

/*
  MyVector Class Design:
  - Internal Array: Dynamically allocate memory for storing elements.
  - Dynamic Resizing: Implement a resize function to double capacity when full.
  - Methods:
    1. Constructor: Initialize with default capacity.
    2. Destructor: Free allocated memory.
    3. push_back: Add an element at the end, resizing if necessary.
    4. pop_back: Remove the last element (optional).
    5. operator[]: Provide access to elements by index.
    6. size(): Return the current number of elements.
    7. cpacity(): Return the total allocated capacity.
*/


template<typename T>
class MyVector {
private:
    int data_size;
    int data_in_use = 0; // amount of indexes with in used data
    T *data;

    void resize(int new_data_size) {
        T *new_data = new T[new_data_size];
        for (int i = 0; i < data_size; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        data_size = new_data_size;
    }
public:
    MyVector(int size = 0) {
        this->data_size = size;
        data = new T[size];
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(T value) {
        if (data_in_use == data_size) {
            resize(data_size + 1); // resizes the dynamic array so a new value can be added
        }
        data[data_in_use] = value;
        data_in_use++;
    }

    T pop_back() {
        if (data_in_use == 0)
            throw logic_error("Cannot pop back from an empty vector");
        T value = data[--data_in_use];
        return value;
    }

    T& at(const int &pos) {
        if (pos >= data_in_use || pos < 0)
            throw out_of_range("Cannot get an un created element");
        return data[pos];
    }

    int find(T value) {
        int index {-1};
        for (int i = 0; i < data_in_use; ++i) {
            if (data[i] == value) {
                index = i;
                return index;
            }
        }

        throw logic_error("Value isn't inside data");
    }

    bool clear() {
        for (int i = 0; i < data_in_use; ++i) {
            data[i] = T();
        }
        data_in_use = 0;
        return true;
    }

    int size() const {
        return this->data_size;
    }

    int capacity() const {
        return this->capacity();
    }

    T& operator[](const int &index) {
        if (index >= data_in_use || index < 0)
            throw out_of_range("Index out of bounds");
        return data[index];
    }

    T* begin() { return data; }
    T* end() { return data + data_in_use; }
    const T* begin() const { return data; }
    const T* end() const { return data + data_in_use; }

};

//
//int main() {
//    // Test 1: Basic Functionality
//    cout << "==== Test 1: Basic Functionality ====" << endl;
//    MyVector<int> vec1;
//    vec1.push_back(10);
//    vec1.push_back(20);
//    vec1.push_back(30);
//
//    cout << "Vector size: " << vec1.size() << endl;
//    for (int i = 0; i < vec1.size(); ++i) {
//        cout << "Element at index " << i << ": " << vec1.at(i) << endl;
//    }
//    cout << endl;
//
//    // Test 2: Modifications
//    cout << "==== Test 2: Modifications ====" << endl;
//    vec1.at(1) = 99; // Modify element at index 1
//    cout << "After modification, element at index 1: " << vec1.at(1) << endl;
//    vec1.at(2) = 50; // Modify element at index 2
//    cout << "After modification, element at index 2: " << vec1.at(2) << endl;
//    cout << endl;
//
//    // Test 3: Out-of-Bounds Access
//    cout << "==== Test 3: Out-of-Bounds Access ====" << endl;
//    try {
//        cout << vec1.at(4); // Invalid index, should throw exception
//    } catch (const exception& e) {
//        cerr << "Caught exception: " << e.what() << endl;
//    }
//    cout << endl;
//
//    // Test 4: Stress Test with Large Data
//    cout << "==== Test 4: Large Data Test ====" << endl;
//    MyVector<int> largeVec;
//    for (int i = 0; i < 1000; ++i) {
//        largeVec.push_back(i);
//    }
//    cout << "Large vector size: " << largeVec.size() << endl;
//    cout << "First element: " << largeVec.at(0) << endl;
//    cout << "Last element: " << largeVec.at(999) << endl;
//    cout << endl;
//
//    try {
//        cout << endl;
//        cout << vec1.find(1);
//    }
//    catch (const exception& e) {
//        cerr << "Caught exception: " << e.what() << endl;
//    }
//
//    return 0;
//}
