#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Data Types/vector.cpp"
#include "Data Types/queue.cpp"
using namespace std;



/**
 * @brief AVLTree class
 *
 * This class provides a skeleton for an AVL Tree, a self-balancing Binary Search Tree (BST).
 * It maintains the height balance property: for any node, the difference in heights
 * of the left and right subtrees is at most 1.
 *
 * You will need to implement the functions yourself. The provided structure and comments
 * guide you on what each function is expected to do.
 */
template<typename T>
class AVLTree {
private:
    /**
     * @brief A single node in the AVL Tree.
     *
     * Each node stores:
     * - A key (we use 'int' for simplicity, but this could be templated)
     * - Left and right child pointers
     * - A height field for maintaining AVL balance
     * - An optional subtree_size field (for order-statistic operations)
     */
    struct Node {
        T key;
        Node* left;
        Node* right;
        int height;
        int subtree_size;

        Node(int k)
                : key(k), left(nullptr), right(nullptr), height(1), subtree_size(1) {}
    };

    Node* root;

    int getHeight(Node* node) {
        return (node) ? node->height: 0;
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalanceFactor(Node* node) {
        return getHeight(node->left) - getHeight(node->right);
    }

    int size(Node* node) {
        return (node) ? node->subtree_size : 0;
    }

    void updateAugmentedData(Node* node) {
        updateHeight(node);
        node->subtree_size = 1 + size(node->left) + size(node->right);
    }

    // --- Rotations ---

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(x);
        updateHeight(y);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T1 = y->left;

        y->left = x;
        x->right = T1;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // --- Balancing ---

    Node* balanceNode(Node* node) {
        int balance = getBalanceFactor(node);

        // LL (Left Left Rotation)
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }

        // LR (Left Right Rotation)
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RR (Right Right Rotation)
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }

        // RL (Right Left Rotation)
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // --- Insertion ---

    Node* insertNode(Node* node, T key) {
        if (node == nullptr)
            return new Node(key);
        if (key > node->key) {
            node->right = insertNode(node->right, key);
        } else {
            node->left = insertNode(node->left, key);
        }

        updateAugmentedData(node);
        return balanceNode(node);
    }

    Node* insertNode_BFS(Node* node, T key) {

    }

    // --- Finding Minimum ---

    Node* findMinNode(Node* node) {
        if (node->left == nullptr) return node;
        return findMinNode(node->left);
    }

    // --- Deletion ---
    Node* removeNode(Node*& node) {
        if (node->right == nullptr && node->left == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            node = temp;
        } else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            node = temp;
        } else {
            Node* temp = findMinNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    Node* deleteNode(Node* node, T key) {
        if (node == nullptr) return nullptr;

        if (key > node->key) {
            node->right = deleteNode(node->right, key);
        }
        else if (key < node->key) {
            node->left = deleteNode(node->left, key);
        }
        else if (node->key == key) {
            removeNode(node, key);
        }

        updateAugmentedData(node);
        return balanceNode(node);
    }

    // --- Searching ---
    bool searchNode(Node* node, T key) {
        while (node != nullptr) {
            if (node->key == key) {
                return true;
            } else if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return false;
    }


    // --- Traversals ---

    void inOrderTraversal(Node* node) {
        if (node == nullptr) return;
        inOrderTraversal(node->left);
        cout << node->key << " ";
        inOrderTraversal(node->right);
    }

    // --- Clearing the Tree ---

    void clearSubtree(Node* node) {
        if (node == nullptr) {
            return;
        }

        clearSubtree(node->left);
        clearSubtree(node->right);

        delete node;
    }

    // --- Advanced Operations (Optional) ---

    Node* buildAVLFromSortedArray(const Vector<int>& keys) {
        Node* subtree_root;
        for (int i : keys) {
            insertNode(subtree_root, i);
        }
    }

    /**
    * @brief Merge another AVL tree into the current one.
    * One approach:
            * 1) Extract keys from both trees (in-order).
    * 2) Merge the two sorted arrays of keys.
    * 3) Rebuild a balanced AVL tree from the merged array.
    * @param other Another AVLTree to merge with.
    */
    void mergeWith(AVLTree& other);

    /**
     * @brief Return the i-th smallest element in the subtree rooted at 'node'.
     * Uses subtree_size to find the element in O(log n).
     * @param node Subtree root.
     * @param i The rank of the desired element (1-based).
     * @return int The i-th smallest key.
     */
    T selectNode(Node* node, T i);

    /**
     * @brief Return the rank of a given key in the subtree rooted at 'node'.
     * Rank is the position of the key in sorted order (1-based).
     * @param node Subtree root.
     * @param key The key whose rank is desired.
     * @return int The rank of the key; 0 if not found.
     */
    int rankOfKey(Node* node, T key);

public:
    /**
     * @brief Construct an empty AVLTree.
     */
    AVLTree();

    /**
     * @brief Insert a key into the AVL tree.
     * @param key The key to insert.
     */
    void insert(T key);

    /**
     * @brief Remove a key from the AVL tree.
     * @param key The key to remove.
     */
    void remove(T key);

    /**
     * @brief Check if a key is present in the AVL tree.
     * @param key The key to search for.
     * @return true If the key is found.
     * @return false Otherwise.
     */
    bool search(T key);

    /**
     * @brief Print the AVL tree's keys in ascending order.
     */
    void printInOrder();

    /**
     * @brief Get the height of the entire AVL tree.
     * @return int The height of the tree.
     */
    int getTreeHeight();

    /**
     * @brief Remove all nodes from the AVL tree, making it empty.
     */
    void clear();

    /**
     * @brief Merge another AVLTree into this one, producing a balanced tree.
     * @param other The other AVLTree to merge.
     */
    void merge(AVLTree& other);

    /**
     * @brief Get the i-th smallest element in the AVL tree.
     * @param i The rank (1-based) of the desired element.
     * @return int The i-th smallest key.
     */
    int select(int i);

    /**
     * @brief Get the rank of a given key in the AVL tree.
     * @param key The key whose rank is to be determined.
     * @return int The rank of the key; 0 if the key is not found.
     */
    int rank(T key);
};


int main() {



    return 0;
}