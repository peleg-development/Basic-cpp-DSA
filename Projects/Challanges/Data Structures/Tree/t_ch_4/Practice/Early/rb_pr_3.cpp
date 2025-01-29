#include <iostream>
using namespace std;

/**
 * @brief RedBlackTree class
 *
 * This class provides a skeleton for a generic Red-Black Tree, which stores key-value pairs.
 * It maintains the following properties:
 * 1) Every node is either red or black.
 * 2) The root is black.
 * 3) All leaves (NIL nodes) are black.
 * 4) If a red node has children, they must be black (no two red nodes can be adjacent).
 * 5) Every path from a node to its descendant NIL nodes contains the same number of black nodes.
 */

template <typename K, typename V>
class RedBlackTree {
    struct Node {
        K key;
        V value;
        bool isRed;
        Node* parent;
        Node* left;
        Node* right;

        Node(K k, V v)
                : key(k), value(v), isRed(true), parent(nullptr), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;
    Node* NIL;  // Sentinel node to represent all leaves
    int size;

    void initializeNIL() {
        NIL = new Node(K{}, V{});
        NIL->isRed = false;
        NIL->left = NIL->right = nullptr;
    }

    void updateParents(Node*& oldRoot, Node*& newRoot) {
        newRoot->parent = oldRoot->parent;
        if (oldRoot->parent == nullptr) {
            root = newRoot;
        } else if (oldRoot->parent->right == oldRoot) {
            oldRoot->parent->right = newRoot;
        } else {
            oldRoot->parent->left = newRoot;
        }
    }

    void leftRotate(Node* oldRoot) {
        Node* newRoot = oldRoot->right;
        Node* newRootLeftChild = newRoot->left;

        oldRoot->right = newRootLeftChild;
        if (oldRoot->right != nullptr ) {
            oldRoot->right->parent = oldRoot;
        }

        updateParents(oldRoot, newRoot);

        newRoot->left = oldRoot;
        oldRoot->parent = newRoot;
    }

    void rightRotate(Node* oldRoot) {
        Node* newRoot = oldRoot->left;
        Node* newRootRightChild = newRoot->right;

        oldRoot->left = newRootRightChild;
        if (oldRoot->left != nullptr) {
            oldRoot->left->parent = oldRoot;
        }

        updateParents(oldRoot, newRoot);

        newRoot->right = oldRoot;
        oldRoot->parent = newRoot;
    }

    void recolorNodes(Node*& node, Node*& aunt) {
        node->parent->isRed = false;
        aunt->isRed = false;
        node->parent->parent->isRed = true;
    }

    Node* getAunt(const Node* node) {
        if (!node || !node->parent || !node->parent->parent) {
            return nullptr;
        }
        if (node->parent == node->parent->parent->left) {
            return node->parent->parent->right;
        } else {
            return node->parent->parent->left;
        }
    }



    void fixInsert(Node* node) {
        while (node && node->parent->isRed) {
            Node* aunt = getAunt(node);

            if (aunt && aunt->isRed) {
                recolorNodes(node, aunt);
                node = node->parent->parent;
            } else {
                if (node->parent == node->parent->parent->left) {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rightRotate(node->parent->parent);
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    leftRotate(node->parent->parent);
                }
            }

        }
        root->isRed = false;
    }

    Node* findMin(Node* node) {
    }

    void transplant(Node* u, Node* v) {

    }

    void clearSubtree(Node* node) {

    }

    void printInOrder(Node* node) {

    }

    bool search(Node* node, K key) {

    }

public:
    RedBlackTree() : root(nullptr), size(0) {
        initializeNIL();
        root = NIL;
    }

    ~RedBlackTree() {
        clear();
        delete NIL;
    }

    void insert(K key, V value) {

    }

    void remove(K key) {
        // Removal logic here (omitted for brevity)
    }

    bool search(K key) {
        return search(root, key);
    }

    void printInOrder() {
        printInOrder(root);
    }

    void clear() {
        clearSubtree(root);
        root = NIL;
    }
};

// Test cases in main.cpp
int main() {
    RedBlackTree<int, std::string> rbTree;

    // Test insertion
    rbTree.insert(10, "Ten");
    rbTree.insert(20, "Twenty");
    rbTree.insert(15, "Fifteen");

    std::cout << "In-order traversal after insertions: ";
    rbTree.printInOrder();

    // Test search
    std::cout << "\nSearching for 15: " << (rbTree.search(15) ? "Found" : "Not Found") << std::endl;

    // Test deletion
    rbTree.remove(15);
    std::cout << "In-order traversal after deletion: ";
    rbTree.printInOrder();

    // Test clear
    rbTree.clear();
    std::cout << "\nTree cleared.\n";

    return 0;
}

