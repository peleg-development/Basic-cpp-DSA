#include <iostream>
#include <stdexcept>
#include <queue>

using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};


class Tree {
private:
    Node* root;

public:
    Tree(int root_value) {
        root = new Node(root_value);
    }

    ~Tree() {
        delete root;
    }

    Node* findParentNode(int value, Node* current_node) {
        while (current_node) {
            if (value < current_node->value) {
                if (!current_node->left) return current_node;
                current_node = current_node->left;
            } else {
                if (!current_node->right) return current_node;
                current_node = current_node->right;
            }
        }
        return nullptr;
    }

    void insert(int value) {
        if (!root) {
            root = new Node(value);
            return;
        }

        Node* parent = findParentNode(value, root);

        if (value < parent->value) {
            parent->left = new Node(value);
        } else {
            parent->right = new Node(value);
        }
    }

    bool search(int value) {
        Node* current = root;

        while (current) {
            if (value == current->value) {
                return true;
            }
            if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return false;
    }



    void remove(int value) {
        Node* parent = findParentNode(value, root);
        if (value < parent->value) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
    }

    int findMin();                  // Find the minimum value in the tree
    int findMax();                  // Find the maximum value in the tree
    int height();                   // Calculate the height of the tree
    void traverseInOrder();         // Traverse the tree in-order
    void traversePreOrder();        // Traverse the tree pre-order
    void traversePostOrder();       // Traverse the tree post-order

    void printTree(Node* node, int space = 0, int gap = 5) {
        if (!node) return;

        space += gap;

        printTree(node->right, space);

        for (int i = gap; i < space; i++) {
            cout << " ";
        }
        cout << node->value << endl;

        printTree(node->left, space);
    }

    void printTree() {
        printTree(root);
    }

};


int main() {
    auto *a = new Tree(4);
    a->insert(5);
    a->insert(3);
    a->insert(7);
    a->insert(2);
    a->printTree();

    cout << a->search(7) << endl;

    return 0;
}