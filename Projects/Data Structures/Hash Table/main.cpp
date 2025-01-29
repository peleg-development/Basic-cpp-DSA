#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    string key;
    int value;
    Node* next;

    Node(const string& key, int value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

class HashTable {
private:
    static const int SIZE = 7;
    Node* dataMap[SIZE];
    int numElements;

public:
    HashTable() {
        for (int i = 0; i < SIZE; ++i) {
            dataMap[i] = nullptr;
        }
        numElements = 0;
    }
    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            Node* current = dataMap[i];
            while (current != nullptr) {
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }
    }

    int hashFunction(const string& key) {
        int hash = 0;
        for (unsigned char i : key) {
            int asciiValue = int(i);
            hash = (hash + asciiValue * 23) % SIZE;
        }
        return hash;
    }

    void insert(const string& key, int value) {
        int index = hashFunction(key);
        Node* newNode = new Node(key, value);
        if (dataMap[index] == nullptr) {
            dataMap[index] = newNode;
        } else {
            Node* temp = dataMap[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        numElements++;
    }

    bool remove(const string& key) {
        int index = hashFunction(key);
        Node* current = dataMap[index];
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (previous == nullptr) {
                    dataMap[index] = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                numElements--;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    int search(const string& key) {
        int index = hashFunction(key);
        Node* temp = dataMap[index];
        while (temp != nullptr) {
            if (temp->key == key) {
                return temp->value;
            }
            temp = temp->next;
        }
        return -1;
    }

    void printTable() {
        for (int i = 0; i < SIZE; i++) {
            cout << i << ":";
            Node* temp = dataMap[i];
            while (temp != nullptr) {
                cout << " {" << temp->key << ", " << temp->value << "}";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    vector<string> keys() {
        vector<string> allKeys;
        for (int i = 0; i < SIZE; i++) {
            Node* temp = dataMap[i];
            while (temp != nullptr) {
                allKeys.push_back(temp->key);
                temp = temp->next;
            }
        }
        return allKeys;
    }

    bool containsKey(const string& key) {
        int index = hashFunction(key);
        Node* temp = dataMap[index];
        while (temp != nullptr) {
            if (temp->key == key) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    int getSize() {
        return numElements;
    }

    void clear() {
        for (int i = 0; i < SIZE; i++) {
            Node* current = dataMap[i];
            while (current != nullptr) {
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
            dataMap[i] = nullptr;
        }
        numElements = 0;
    }

    float loadFactor() {
        return static_cast<float>(numElements) / SIZE;
    }
};

int main() {
    HashTable hashTable;

    hashTable.insert("apple", 100);
    hashTable.insert("banana", 200);
    hashTable.insert("grape", 300);
    hashTable.insert("orange", 400);
    hashTable.insert("melon", 500);

    cout << "Hash Table Table after insertions:" << endl;
    hashTable.printTable();

    cout << "\nSearching for 'banana': " << hashTable.search("banana") << endl;
    cout << "Searching for 'cherry': " << hashTable.search("cherry") << endl;

    bool removed = hashTable.remove("grape");
    cout << "\nRemoving 'grape': " << (removed ? "Successful" : "Not found") << endl;

    cout << "\nHash Table Table after deletion:" << endl;
    hashTable.printTable();

    vector<string> allKeys = hashTable.keys();
    cout << "\nAll keys in the hash table:" << endl;
    for (const string& key : allKeys) {
        cout << key << endl;
    }

    cout << "\nContains 'apple': " << (hashTable.containsKey("apple") ? "Yes" : "No") << endl;
    cout << "Contains 'grape': " << (hashTable.containsKey("grape") ? "Yes" : "No") << endl;

    cout << "\nCurrent size of hash table: " << hashTable.getSize() << endl;
    cout << "Current load factor: " << hashTable.loadFactor() << endl;

    hashTable.clear();
    cout << "\nHash Table table after clearing:" << endl;
    hashTable.printTable();
    cout << "Current size of hash table: " << hashTable.getSize() << endl;

    return 0;
}
