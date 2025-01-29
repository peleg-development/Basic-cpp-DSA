#include <iostream>
#include <stdexcept>
using namespace std;
//
//class Queue {
//private:
//    int* arr;        // Pointer to the array
//    int capacity;    // Total capacity of the queue
//    int front;       // Index of the front element
//    int rear;        // Index of the rear element
//    int count;       // Number of elements in the queue
//
//    void resize(int newCapacity) {
//        int* new_arr = new int[newCapacity];
//        for (int i = 0; i < count; ++i) {
//            new_arr[i] = arr[(front + i) % capacity];
//        }
//        delete[] arr;
//        arr = new_arr;
//        front = 0;
//        rear = count;
//        capacity = newCapacity;
//    }
//
//public:
//    Queue(int initialCapacity = 4) {
//        arr = new int[initialCapacity];
//        capacity = initialCapacity;
//        front = 0;
//        rear = 0;
//        count = 0;
//    }
//
//    ~Queue() {
//        delete[] arr;
//    }
//
//    void enqueue(int value) {
//        if (count == capacity) {
//            resize(capacity * 2);
//        }
//        arr[rear] = value;
//        rear = (rear + 1) % capacity;
//        count++;
//    }
//
//    int dequeue() {
//        if (isEmpty()) {
//            throw runtime_error("Queue is empty. Cannot dequeue.");
//        }
//        int value = arr[front];
//        front = (front + 1) % capacity;
//        count--;
//        if (count > 0 && count == capacity / 4) {
//            resize(capacity / 2);
//        }
//        return value;
//    }
//
//    int peekFront() {
//        if (isEmpty()) {
//            throw runtime_error("Queue is empty. Cannot peek.");
//        }
//        return arr[front];
//    }
//
//    int peekRear() {
//        if (isEmpty()) {
//            throw runtime_error("Queue is empty. Cannot peek.");
//        }
//        return arr[(rear - 1 + capacity) % capacity];
//    }
//
//    bool isEmpty() {
//        return count == 0;
//    }
//
//    int size() {
//        return count;
//    }
//
//    int getCapacity() {
//        return capacity;
//    }
//
//    void printQueue() {
//        for (int i = 0; i < count; ++i) {
//            cout << arr[(front + i) % capacity] << " ";
//        }
//        cout << endl;
//    }
//};



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

//
//static void Queuetest() {
//    try {
//        Queue queue;
//
//        // Test 1: Initial state
//        cout << "Test 1: Queue is initially empty - ";
//        if (queue.isEmpty()) {
//            cout << "Passed\n";
//        } else {
//            cout << "Failed\n";
//        }
//
//        // Test 2: Enqueue operation
//        queue.enqueue(5);
//        queue.enqueue(10);
//        queue.enqueue(15);
//        cout << "Test 2: Enqueue elements - ";
//        if (queue.size() == 3 && queue.front() == 5) {
//            cout << "Passed\n";
//        } else {
//            cout << "Failed\n";
//        }
//
//        // Test 3: Dequeue operation
//        queue.dequeue();
//        cout << "Test 3: Dequeue operation - ";
//        if (queue.size() == 2 && queue.front() == 10) {
//            cout << "Passed\n";
//        } else {
//            cout << "Failed\n";
//        }
//
//        // Test 4: Enqueue after dequeuing
//        queue.enqueue(20);
//        cout << "Test 4: Enqueue after dequeue - ";
//        if (queue.size() == 3 && queue.front() == 10) {
//            cout << "Passed\n";
//        } else {
//            cout << "Failed\n";
//        }
//
//        // Test 5: Dequeue until empty
//        queue.dequeue();
//        queue.dequeue();
//        queue.dequeue();
//        cout << "Test 5: Dequeue until empty - ";
//        if (queue.isEmpty()) {
//            cout << "Passed\n";
//        } else {
//            cout << "Failed\n";
//        }
//
//        // Test 6: Dequeue from an empty queue (should throw exception)
//        cout << "Test 6: Dequeue on empty queue (expect exception) - ";
//        try {
//            queue.dequeue();
//            cout << "Failed\n"; // Exception not thrown
//        } catch (const out_of_range&) {
//            cout << "Passed\n"; // Exception thrown as expected
//        }
//
//    } catch (...) {
//        cerr << "An unexpected error occurred during the tests.\n";
//    }
//
//}