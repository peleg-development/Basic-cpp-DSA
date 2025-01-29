#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Node {
public:
    T value;
    Node* next;

    Node(T value) {
        this->value = value;
        this->next = nullptr;
    }
};

template <typename T>
class Queue {
private:
    Node<T>* first;  // Pointer to the first node in the queue
    Node<T>* last;   // Pointer to the last node in the queue
    int length;      // Number of elements in the queue

public:
    // Constructor to initialize an empty queue
    Queue() {
        first = nullptr;
        last = nullptr;
        length = 0;
    }

    // Destructor to free memory
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Adds a new value to the end of the queue
    void enqueue(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (first == nullptr) {
            last = new_node;
            first = new_node;
        } else {
            last->next = new_node;
            last = new_node;
        }
        length++;
    }

    // Removes the first element from the queue
    void dequeue() {
        if (first == nullptr) {
            throw std::out_of_range("Cannot dequeue from an empty queue");
        }

        Node<T>* temp = first;
        first = first->next;

        if (first == nullptr) {
            last = nullptr;
        }

        delete temp;
        length--;
    }

    // Returns the value of the first element in the queue
    T front() const {
        if (first == nullptr) {
            throw std::out_of_range("Queue is empty. Cannot access front.");
        }
        return first->value;
    }

    // Checks if the queue is empty
    bool isEmpty() const {
        return first == nullptr;
    }

    // Returns the number of elements in the queue
    int size() const {
        return length;
    }
};
