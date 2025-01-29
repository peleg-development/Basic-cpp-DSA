#include <iostream>
#include <stdexcept>
#include <queue>
#include <memory>

using namespace std;

template <typename T>
class RecursiveTree {
public:
    RecursiveTree(T value) {
        root = new Node(value);
    }

    ~RecursiveTree() {
        deleteTree(root);
    }

    void insert(T value) {
        insert(root, value);
    }

    void remove(T value) {
        root = remove(root, value);
    }

    bool search(T value) const {
        return search(root, value);
    }

    void printInOrder() const {
        printInOrder(root, 0, 5);
        cout << endl;
        cout << endl;
        cout << endl;
    }

protected:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node* &node, T value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value > node->data) {
            insert(node->right, value);
        } else {
            insert(node->left, value);
        }
    }

    Node* remove(Node* node, T value) {
        if (!node) return nullptr;
        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* successor = getMinNode(node->right);
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
        }
        return node;
    }

    Node* getMinNode(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void printInOrder(Node* node, int space, int gap) const {
        if (!node) return;
        space += gap;
        printInOrder(node->right, space, gap);
        for (int i = gap; i < space; i++) {
            cout << " ";
        }
        cout << node->data << endl;
        printInOrder(node->left, space, gap);
    }

    bool search(Node* node, T value) const {
        if (!node) return false;
        if (node->data == value) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

int main() {
    RecursiveTree<int> tree(5);
    tree.insert(10);
    tree.insert(3);
    tree.insert(7);
    tree.insert(15);
    tree.insert(20);
    tree.insert(2);
    tree.printInOrder();

    cout << "Removing 20: " << (tree.search(20) ? "Found" : "Not Found") << endl;
    tree.remove(20);
    cout << "After Removal: " << (tree.search(20) ? "Found" : "Not Found") << endl;
    tree.printInOrder();

    cout << "Removing 15: " << (tree.search(15) ? "Found" : "Not Found") << endl;
    tree.remove(15);
    cout << "After Removal: " << (tree.search(15) ? "Found" : "Not Found") << endl;
    tree.printInOrder();

    cout << "Removing 5: " << (tree.search(5) ? "Found" : "Not Found") << endl;
    tree.remove(5);
    cout << "After Removal: " << (tree.search(5) ? "Found" : "Not Found") << endl;
    tree.printInOrder();

    cout << "Removing 10: " << (tree.search(10) ? "Found" : "Not Found") << endl;
    tree.remove(10);
    cout << "After Removal: " << (tree.search(10) ? "Found" : "Not Found") << endl;
    tree.printInOrder();

    cout << "Removing 99: " << (tree.search(99) ? "Found" : "Not Found") << endl;
    tree.remove(99);
    cout << "After Removal: " << (tree.search(99) ? "Found" : "Not Found") << endl;
    tree.printInOrder();

    return 0;
}
