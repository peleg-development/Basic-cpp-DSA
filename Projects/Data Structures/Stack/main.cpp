#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;        // Pointer to the array
    int capacity;    // Total capacity of the stack
    int top;         // Index of the top element

public:
    void resize(int size) {
        int* new_arr = new int[size];
        for (int i = 0; i < capacity; ++i) {
            new_arr[i] = arr[i];
        }
        capacity = size;
        delete[] arr;
        arr = new_arr;
    }

    Stack(int first) {
        capacity = 1;
        arr = new int[1]{first};
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int value) {
        top = capacity;
        resize(capacity + 1);
        arr[top] = value;
    }

    int pop() {
        int old_top = top;
        resize(capacity - 1);
        top = capacity - 1;
        return old_top;
    }

    int peek() {
        return top;
    };

    bool isEmpty() {
        if (top == -1)
            return true;
        return false;
    }

    int size() {
        return capacity;
    }

    void printStack() {
        for (int i = 0; i < capacity; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};


int main() {
    auto *a = new Stack(4);
    a->push(2);
    a->printStack();

    a->push(44);
    a->printStack();
    a->pop();
    a->printStack();

    cout << a->peek() << endl;
    a->push(44);
    a->push(44);
    a->push(44);
    a->printStack();

    return 0;
}