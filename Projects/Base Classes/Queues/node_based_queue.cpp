#include <iostream>
#include <stdexcept>

using namespace std;

/*
Challenge: Advanced Node-Based Queue Class

Objective:
- To design a queue using a node-based implementation for improved understanding of linked structures.

Features to implement:
1. Node-based queue implementation (linked list structure).
2. Dynamic memory allocation for queue elements.
3. Iterator support to traverse the queue elements.
4. Peek at any position in the queue by traversing nodes.
5. Support for reversing the queue (optional challenge).
6. Optimization for memory usage and access times.

What is a Node-Based Queue?
- A linear data structure implemented using nodes where each node contains data and a pointer to the next node.
- Grows dynamically without the need for resizing.

Characteristics:
- Efficient O(1) enqueue and dequeue operations.
- Dynamically allocated memory ensures no wasted capacity.

Common operations:
- enqueue(value): Add an element to the rear of the queue.
- dequeue(): Remove and return the element from the front.
- front(): Access the element at the front without removing it.
- size(): Returns the number of elements.
- empty(): Check if the queue is empty.
- reverse(): Reverse the order of elements in the queue (optional).
*/

template<typename T>
class NodeQueue {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    size_t length;

public:
    NodeQueue() : frontNode(nullptr), rearNode(nullptr), length(0) {}

    ~NodeQueue() {
        // Clean up all allocated nodes.
    }

    // Add an element to the rear of the queue.
    void enqueue(const T& value) {
        // Create a new node and add it to the rear of the queue.
    }

    // Remove and return the element from the front of the queue.
    T dequeue() {
        // Remove the front node and return its value.
    }

    // Access the front element without removing it.
    T& front() const {
        // Return the data in the front node.
    }

    // Peek at any position in the queue.
    T& peek(size_t index) const {
        // Traverse the nodes to access the element at the specified index.
    }

    // Return the current size of the queue.
    size_t size() const {
        // Return the number of elements in the queue.
    }

    // Check if the queue is empty.
    bool empty() const {
        // Return true if the queue is empty, false otherwise.
    }

    // Clear all elements from the queue.
    void clear() {
        // Remove all nodes from the queue.
    }

    // Reverse the order of elements in the queue (optional challenge).
    void reverse() {
        // Reverse the linked structure of the queue.
    }

};
