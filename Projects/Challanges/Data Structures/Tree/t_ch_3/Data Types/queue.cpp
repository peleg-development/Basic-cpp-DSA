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
class Queue {
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
    Queue() : frontNode(nullptr), rearNode(nullptr), length(0) {}

    ~Queue() {
        while (!empty()) {
            dequeue();
        }
    }

    void enqueue(const T& value) {
        Node* temp = new Node(value);
        if (frontNode == nullptr) {
            frontNode = temp;
            rearNode = temp;
        } else {
            rearNode->next = temp;
            rearNode = temp;
        }
        length++;
    }

    T dequeue() {
        if (frontNode == nullptr) {
            throw out_of_range("Cannot dequeue from an empty queue");
        }

        Node* temp = frontNode;
        T data = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        --length;
        return data;
    }

    T& front() const {
        return frontNode->data;
    }

    T& peek(size_t index) const {
        if (index >= length) {
            throw out_of_range("cannot access element not in bounds");
        }
        Node* temp = frontNode;
        for (size_t i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    size_t size() const {
        return length;
    }

    bool empty() const {
        if (frontNode == nullptr)
            return true;
        return false;
    }

    void clear() {
        while (!empty()) {
            dequeue();
        }
    }

    void reverse() {
        if (frontNode == nullptr) {
            return;
        }

        T data = dequeue();

        reverse();
        enqueue(data);
    }


};
