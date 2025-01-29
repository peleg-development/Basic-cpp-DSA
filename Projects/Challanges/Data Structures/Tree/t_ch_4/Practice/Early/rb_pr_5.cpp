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
        } else if (oldRoot == oldRoot->parent->left) {
            oldRoot->parent->left = newRoot;
        } else {
            oldRoot->parent->right = newRoot;
        }
    }

    void leftRotate(Node* oldRoot) {
        Node* newRoot = oldRoot->right;
        oldRoot->right = newRoot->left;

        if (newRoot->left != NIL) {
            newRoot->left->parent = oldRoot;
        }

        updateParents(oldRoot, newRoot);

        newRoot->left = oldRoot;
        oldRoot->parent = newRoot;
    }

    void rightRotate(Node* oldRoot) {
        Node* newRoot = oldRoot->left;
        oldRoot->left = newRoot->right;

        if (newRoot->right != NIL) {
            newRoot->right->parent = oldRoot;
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

    void insertionRotation(Node*& node) {
        if (node->parent->parent->right == node->parent) {
            if (node == node->parent->left) {
                node = node->parent;
                rightRotate(node);
            }

            node->parent->isRed = false;
            node->parent->parent->isRed = true;
            leftRotate(node->parent->parent);
        } else {
            if (node == node->parent->right) {
                node = node->parent;
                leftRotate(node);
            }

            node->parent->isRed = false;
            node->parent->parent->isRed = true;
            rightRotate(node->parent->parent);
        }
    }

    void fixInsert(Node* node) {
        while (node && node->parent->isRed) {
            Node* aunt = getAunt(node);
            if (aunt->isRed) {
                recolorNodes(node, aunt);
                node = node->parent->parent;
            } else {
                insertionRotation(node);
            }

        }
        root->isRed = false;
    }

    Node* findMin(Node* node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

    /**
     * @brief Transplant a subtree rooted at 'u' with a subtree rooted at 'v'.
     * Replaces the subtree at 'u' with the subtree at 'v'.
     * @param u The node to replace.
     * @param v The replacement node.
     */
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }

        v->parent = u->parent;
    }

    /**
     * @brief Fix the Red-Black Tree properties after a deletion.
     * Rebalances the tree by adjusting colors and performing rotations as needed.
     * @param node The node to fix.
     */
    void fixDelete(Node* node) {

    }


    void deleteNode(Node* target) {
        // cases:
        // 1) node we want to delete has a NIL left child
        // 2) node we want to delete has a NIL right child
        // 3) node we want to delete has left and right nodes arent NIL
        Node* removedNode = target;
        bool nodeRemovedOriginalColor = removedNode->isRed;
        Node* replacement = nullptr;

        if (target->right != nullptr && target->left == nullptr) {
            replacement = target->right;
            transplant(target, replacement);
        } else if (target->right == nullptr && target->left != nullptr) {
            replacement = target->left;
            transplant(target, replacement);
        } else {
            Node* successor = findMin(target->right);

            removedNode = successor;
            nodeRemovedOriginalColor = successor->isRed;

            if (successor->parent != target) {
                transplant(successor, successor->right);
                successor->right = target->right;
                target->right->parent = successor;
            }

            transplant(target, successor);

            successor->left = target->left;
            target->left->parent = successor;
            successor->isRed = target->isRed;
        }

        if (!nodeRemovedOriginalColor) {
            fixDelete(replacement);
        }
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
        Node* newNode = new Node(key, value);
        newNode->left = newNode->right = NIL;

        Node* parent = nullptr;
        Node* current = root;

        while (current != NIL) {
            parent = current;
            if (key > current->key) {
                current = current->right;
            } else if (key < current->key) {
                current = current->left;
            } else {
                delete newNode;
                return;
            }
        }

        newNode->parent = parent;
        if (parent == nullptr) {
            root = newNode;
        } else if (key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        fixInsert(newNode);

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

