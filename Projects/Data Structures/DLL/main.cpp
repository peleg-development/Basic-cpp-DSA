#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node(int value) {
        this->value = value;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int length = 0;
public:
    explicit DoublyLinkedList(int value) {
        Node* newNode = new Node(value);
        head = newNode;
        tail = newNode;
        ++length;
    }

    ~DoublyLinkedList() {
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
        temp->prev = tail;
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
        Node* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        length--;
    }

    void prepend(int value) {
        Node* temp = new Node(value);
        temp->next = head;
        head->prev = temp;
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
        head->prev = nullptr;
        delete temp;
        length--;
    }

    int get(int index) {
        if (index < 0 || index >= length) return -1;
        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->value;
    }

    void set(int index, int value) {
        if (index < 0 || index >= length) return;
        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        temp->value = value;
    }

    void insert(int index, int value) {
        if (index < 0 || index > length) return;
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
        new_node->next = temp->next;
        new_node->prev = temp;
        temp->next->prev = new_node;
        temp->next = new_node;
        length++;
    }

    void deleteNode(int index) {
        if (index < 0 || index >= length) return;
        if (index == 0) {
            deleteFirst();
            return;
        }
        if (index == length - 1) {
            deleteLast();
            return;
        }
        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        length--;
    }

    void reverse() {
        if (!head || !head->next) return;
        Node* current = head;
        Node* temp = nullptr;
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        temp = head;
        head = tail;
        tail = temp;
    }
};

int main() {
    auto* a = new DoublyLinkedList(4);
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
