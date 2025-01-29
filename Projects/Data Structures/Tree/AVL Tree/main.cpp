#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;



/*
Base Class for AVL Tree:
- An AVL Tree is a self-balancing Binary Search Tree (BST).
- Balances the tree by maintaining a balance factor of -1, 0, or +1 for each node.
- Ensures O(log n) time complexity for insertion, deletion, and search operations.
*/

class AVL_Tree {
private:
    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;

        Node(int k)
                : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int getHeight(Node* node) const {
        if (!node)
            return 0;
        return node->height;
    }

    int getBalanceFactor(Node* node) const {
        if (node == nullptr) return 0;
        int leftHeight = (node->left) ? node->left->height : 0;
        int rightHeight = (node->right) ? node->right->height : 0;
        return leftHeight - rightHeight;
    };


    // we rotate right when we are left heavy
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;


        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }


    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T1 = y->left;

        x->left = y;
        y->right = T1;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return y;
    }

    Node* insert(Node* node, int key) {
        Node* a;
        if (node == nullptr)
            return new Node(key);

        if (node->right->key > key) {
            node->right = insert(node->right, key);
        } else if (node->left->key < key) {
            node->left = insert(node->left, key);
        } else {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        // Left-Left (LL) Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right-Right (RR) Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left-Right (LR) Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right-Left (RL) Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return a;
    }

    Node* getMinNode(Node* node) const {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* remove(Node* node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (node->right == nullptr || node->left == nullptr) {
                Node* temp = (node->left) ? node->left: node->right;
                delete node;
                return temp;
            } else {
                Node* temp = getMinNode(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }

        node->height = 1 + max(node->left->height, node->right->height);
        int balance = getBalanceFactor(node);

        // Left-Left (LL) Case
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        // Right-Right (RR) Case
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Left-Right (LR) Case
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateRight(node);
            return rotateLeft(node);
        }

        // Right-Left (RL) Case
        if (balance < -1 && getBalanceFactor(node->left) > 0) {
            node->right = rotateLeft(node);
            return rotateRight(node);
        }

        return node;
    }

    Node* search(Node* node, int key) const {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return search(node->left, key);
        }

        return search(node->right, key);
    }

    void inOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }

        inOrder(node->left);
        cout << node->key << " ";
        inOrder(node->right);
    };

public:
    AVL_Tree(int key) {
        root = new Node(key);
    }

    void insert(int key) {
        Node* new_node = insert(root, key);
    }

    void remove(int key) {
        remove(root, key);
    }

    bool search(int key) const {
        if (search(root, key)->key == key) {
            return true;
        }
        return false;
    }

    void printInOrder() const {
        inOrder(root);
    };
};


int main() {


    return 0;
}