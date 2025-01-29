#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* next = nullptr;

    Node(int value) {
        this->value = value;
    }
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    int length = 0;
public:
    explicit LinkedList(int value) {
        Node* newNode = new Node(value);
        head = newNode;
        tail = newNode;
        ++length;
    }

    ~LinkedList() {
        Node* temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void printList() {
        Node* temp = head;
        while (temp) {
            cout << temp->value << " ";
            temp = temp->next;
        }
    }

    void appendValue(int value) {
        Node* temp = new Node(value);
        tail->next = temp;
        tail = temp;
        length++;
    }

    void deleteLast() {
        if (length == 0) return;

        if (length == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            length--;
            return;
        }

        Node* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = nullptr;
        length--;
    }

    void prepend(int value) {
        Node* temp = new Node(value);
        temp->next = head;
        head = temp;
        length++;
    }

    void deleteFirst() {
        if (head == nullptr) return;

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            length--;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
        length--;
    }

    int get(int index) {
        if (head == nullptr) return -1;

        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->value;
    }

    void set(int index, int value) {
        if (head == nullptr) return;

        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        temp->value = value;
    }

    void insert(int index, int value) {
        if (head == nullptr) return;
        if (index == 0) {
            prepend(value);
            return;
        }
        if (index == length) {
            appendValue(value);
            return;
        }

        Node* new_node = new Node(value);

        Node* temp = head;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }

        Node* temp_next = temp->next;
        temp->next = new_node;
        new_node->next = temp_next;
        length++;
    }

    void deleteNode(int index) {
        if (head == nullptr) return;

        Node* temp = head;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }

        Node* current = temp->next;
        temp->next = current->next;
        current->next = nullptr;
        delete current;
    }

    void reverse() {
        if (!head || !head->next) return;

        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        tail = head;
        head = prev;
    }

};




int main() {
    auto *a = new LinkedList(4);
    a->appendValue(3);
    a->printList();
    a->deleteLast();
    cout << endl;
    a->printList();

    cout << endl;
    a->prepend(45);
    a->printList();

    cout << endl;
    int test = a->get(1);
    cout << test << endl;
    cout << endl;

    a->insert(1, 3);
    a->printList();

    cout << endl;
    a->deleteNode(1);
    a->printList();

    cout << endl;
    a->reverse();
    a->printList();


    return 0;
}

