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
    /**
     * @brief A single node in the Red-Black Tree.
     *
     * Each node stores:
     * - A key (K) for ordering
     * - A value (V) associated with the key
     * - Color (red or black)
     * - Pointers to parent, left, and right children
     */
    struct Node {
        K key;          // Key stored in the node
        V value;        // Value associated with the key
        bool isRed;     // True if the node is red, false if black
        Node* parent;   // Pointer to parent node
        Node* left;     // Pointer to left child
        Node* right;    // Pointer to right child

        Node(K k, V v)
                : key(k), value(v), isRed(true), parent(nullptr), left(nullptr), right(nullptr) {}
    };
private:

    Node* root; // The root node of the Red-Black Tree
    Node* NIL;  // Sentinel NIL node to represent all leaves
    int size {0}; // size value

    // --- Utility Functions ---

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

        Node* newRootLeftSubtree = newRoot->left;
        oldRoot->right = newRootLeftSubtree;

        if (newRootLeftSubtree != nullptr) {
            newRootLeftSubtree->parent = oldRoot;
        }

        updateParents(oldRoot, newRoot);

        newRoot->left = oldRoot;
        oldRoot->parent = newRoot;
    }

    void rightRotate(Node* oldRoot) {
        Node* newRoot = oldRoot->left;

        Node* newRootRightSubtree = newRoot->right;
        oldRoot->left = newRootRightSubtree;

        if (newRootRightSubtree != nullptr) {
            newRootRightSubtree->parent = oldRoot;
        }

        updateParents(oldRoot, newRoot);

        newRoot->right = oldRoot;
        oldRoot->parent = newRoot;
    }


    void recolorNodes(Node*& currentNode, Node*& parentSibling) {
        // Recolor parent to black
        currentNode->parent->isRed = false;

        // Recolor parent's sibling (aunt) to black
        parentSibling->isRed = false;

        // Recolor grandparent to red
        currentNode->parent->parent->isRed = true;
    }

    Node* getAunt(const Node* node) {
        if (node == nullptr || node->parent == nullptr || node->parent->parent == nullptr) {
            return nullptr;
        }

        if (node->parent == node->parent->parent->left) {
            return node->parent->parent->right;
        } else {
            return node->parent->parent->left;
        }
    }

    void fixRotation(Node* node) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        // Case 1: Left-Left (LL)
        if (parent == grandparent->left && node == parent->left) {
            rightRotate(grandparent);
            parent->isRed = false;
            grandparent->isRed = true;
        }
            // Case 2: Right-Right (RR)
        else if (parent == grandparent->right && node == parent->right) {
            leftRotate(grandparent);
            parent->isRed = false;
            grandparent->isRed = true;
        }
            // Case 3: Left-Right (LR)
        else if (parent == grandparent->left && node == parent->right) {
            leftRotate(parent);  // Transform to LL
            fixRotation(parent);   // Recheck and handle as LL
        }
            // Case 4: Right-Left (RL)
        else if (parent == grandparent->right && node == parent->left) {
            rightRotate(parent); // Transform to RR
            fixRotation(parent);   // Recheck and handle as RR
        }
    }


    void fixInsert(Node* node) {
        Node* aunt = getAunt(node);
        if (aunt->isRed) {
            recolorNodes(node, aunt);
        } else {
            fixRotation(node);
        }
    }

    /**
     * @brief Fix the Red-Black Tree properties after a deletion.
     * Rebalances the tree by adjusting colors and performing rotations as needed.
     * @param node The node to fix.
     */
    void fixDelete(Node* node);

    /**
     * @brief Transplant a subtree rooted at 'u' with a subtree rooted at 'v'.
     * Replaces the subtree at 'u' with the subtree at 'v'.
     * @param u The node to replace.
     * @param v The replacement node.
     */
    void transplant(Node* u, Node* v);

    /**
     * @brief Find the minimum node in a subtree.
     * @param node The subtree root.
     * @return Node* The minimum node in the subtree.
     */
    Node* findMin(Node* node);

    /**
     * @brief Clear all nodes from the tree.
     * Recursively deletes all nodes in the tree.
     * @param node The subtree root to clear.
     */
    void clearSubtree(Node* node);

public:
    RedBlackTree() = default;

    ~RedBlackTree() {
        delete root;
    }

    void insert(K key, V value) {
        Node* parent = root;
        while (parent) {
            if (key > parent->key && parent->right) {
                parent = parent->right;
            } else if (key < parent->key && parent->left) {
                parent = parent->left;
            }

            if (!parent->left) {
                parent->left = new Node(key, value);
            } else if (!parent->right) {
                parent->right = new Node(key, value);
            }

            fixInsert(parent);
        }
    }

    /**
     * @brief Remove a key from the Red-Black Tree.
     * @param key The key to remove.
     */
    void remove(K key);

    /**
     * @brief Check if a key is present in the Red-Black Tree.
     * @param key The key to search for.
     * @return true If the key is found.
     * @return false Otherwise.
     */
    bool search(K key);

    /**
     * @brief Print the Red-Black Tree keys in ascending order.
     */
    void printInOrder();

    /**
     * @brief Remove all nodes from the Red-Black Tree, making it empty.
     */
    void clear();
};

// Test cases in main.cpp
int main2() {
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

