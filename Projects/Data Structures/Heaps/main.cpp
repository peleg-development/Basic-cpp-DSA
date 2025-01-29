#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class MaxHeap {
public:
    // Constructor
    MaxHeap() {}

    // Destructor
    ~MaxHeap() {}

    // Insert a value into the heap
    void insert(int value) {
        heap.push_back(value);       // Add the new value to the end of the heap
        heapifyUp(heap.size() - 1);  // Restore the max heap property by heapifying up
    }

    // Extract the maximum value from the heap
    int extractMax() {
        if (isEmpty()) {
            throw logic_error("Heap is empty. Cannot extract max.");
        }
        int maxValue = heap[0];         // The max value is always at the root (index 0)
        heap[0] = heap.back();          // Replace the root with the last element
        heap.pop_back();                // Remove the last element
        if (!isEmpty()) {
            heapifyDown(0);             // Restore the max heap property by heapifying down
        }
        return maxValue;
    }

    // Get the maximum value without removing it
    int getMax() const {
        if (isEmpty()) {
            throw logic_error("Heap is empty. Cannot get max.");
        }
        return heap[0];
    }

    // Get the current size of the heap
    int getSize() const {
        return heap.size();
    }

    // Check if the heap is empty
    bool isEmpty() const {
        return heap.empty();
    }

protected:
    // The underlying container for the heap (array representation)
    vector<int> heap;

    // Helper method to "heapify up" after inserting a value
    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] > heap[parentIndex]) {
                swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    // Helper method to "heapify down" after extracting the max
    void heapifyDown(int index) {
        int size = heap.size();
        while (index < size) {
            int leftChildIndex = 2 * index + 1;
            int rightChildIndex = 2 * index + 2;
            int largestIndex = index;

            if (leftChildIndex < size && heap[leftChildIndex] > heap[largestIndex]) {
                largestIndex = leftChildIndex;
            }

            if (rightChildIndex < size && heap[rightChildIndex] > heap[largestIndex]) {
                largestIndex = rightChildIndex;
            }

            if (largestIndex != index) {
                swap(heap[index], heap[largestIndex]);
                index = largestIndex;
            } else {
                break;
            }
        }
    }

};

// Test cases for the MaxHeap class
void runTests() {
    MaxHeap heap;

    // Test Case 1: Insert elements and check max
    cout << "Test Case 1: Insert elements and get max" << endl;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(30);
    if (heap.getMax() == 30) {
        cout << "Passed: Max is 30 after inserting 10, 20, 5, 30." << endl;
    } else {
        cout << "Failed: Max is not correct after insertions." << endl;
    }

    // Test Case 2: Extract max and verify new max
    cout << "Test Case 2: Extract max" << endl;
    int maxValue = heap.extractMax();
    if (maxValue == 30 && heap.getMax() == 20) {
        cout << "Passed: Extracted max is 30, new max is 20." << endl;
    } else {
        cout << "Failed: Incorrect extraction or new max." << endl;
    }

    // Test Case 3: Insert more elements and verify max
    cout << "Test Case 3: Insert more elements and get max" << endl;
    heap.insert(40);
    if (heap.getMax() == 40) {
        cout << "Passed: Max is 40 after inserting 40." << endl;
    } else {
        cout << "Failed: Max is not correct after insertion." << endl;
    }

    // Test Case 4: Extract all elements
    cout << "Test Case 4: Extract all elements until empty" << endl;
    while (!heap.isEmpty()) {
        cout << "Extracted: " << heap.extractMax() << endl;
    }

    // Test Case 5: Extract from empty heap
    cout << "Test Case 5: Extract from empty heap (expect error)" << endl;
    try {
        heap.extractMax();
        cout << "Failed: No exception thrown for empty heap." << endl;
    } catch (const logic_error& e) {
        cout << "Passed: Correctly threw exception for empty heap." << endl;
    }

    // Test Case 6: Get max from empty heap
    cout << "Test Case 6: Get max from empty heap (expect error)" << endl;
    try {
        heap.getMax();
        cout << "Failed: No exception thrown for getting max from empty heap." << endl;
    } catch (const logic_error& e) {
        cout << "Passed: Correctly threw exception for getting max from empty heap." << endl;
    }
}

int main() {
    runTests();
    return 0;
}
