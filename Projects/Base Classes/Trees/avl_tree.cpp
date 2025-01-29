#pragma once
#include <vector>
#include <iostream>

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
        int key;         // Key stored in the node
        Node* left;      // Pointer to left child
        Node* right;     // Pointer to right child
        int height;      // Height of this node
        int subtree_size; // (Optional) Size of subtree rooted at this node

        Node(int k)
                : key(k), left(nullptr), right(nullptr), height(1), subtree_size(1) {}
    };

    Node* root; // The root node of the AVL Tree

    // --- Basic Utility Functions ---

    /**
     * @brief Get the height of a given node.
     * @param node The node whose height is to be returned.
     * @return int The height of 'node'; 0 if node is nullptr.
     */
    int getHeight(Node* node);

    /**
     * @brief Update the height of a given node based on its children's heights.
     * @param node The node whose height should be updated.
     */
    void updateHeight(Node* node);

    /**
     * @brief Compute the balance factor for a node.
     * The balance factor = height(left subtree) - height(right subtree).
     * @param node The node to evaluate.
     * @return int The balance factor.
     */
    int getBalanceFactor(Node* node);

    /**
     * @brief Updates any augmented data stored in the node (like subtree_size).
     * @param node The node to update after insertions, deletions, or rotations.
     */
    void updateAugmentedData(Node* node);

    // --- Rotations ---

    /**
     * @brief Perform a right rotation to correct a left-heavy subtree.
     * @param y The node around which rotation is performed.
     * @return Node* The new root of the rotated subtree.
     */
    Node* rightRotate(Node* y);

    /**
     * @brief Perform a left rotation to correct a right-heavy subtree.
     * @param x The node around which rotation is performed.
     * @return Node* The new root of the rotated subtree.
     */
    Node* leftRotate(Node* x);

    // --- Balancing ---

    /**
     * @brief Balance the subtree rooted at 'node' after an insertion or deletion.
     * Checks the balance factor and applies rotations if necessary.
     * @param node The subtree root to balance.
     * @return Node* The new root of the balanced subtree.
     */
    Node* balanceNode(Node* node);

    // --- Insertion ---

    /**
     * @brief Insert a key into the subtree rooted at 'node'.
     * Recursively finds the correct position, inserts the node, updates heights,
     * and rebalances if required.
     * @param node The current subtree root where the insertion is applied.
     * @param key The key to insert.
     * @return Node* The new root of the subtree after insertion.
     */
    Node* insertNode(Node* node, int key);

    // --- Finding Minimum ---

    /**
     * @brief Find the node with the minimum key in a subtree.
     * @param node The subtree root from which to find the minimum.
     * @return Node* The node with the minimum key.
     */
    Node* findMinNode(Node* node);

    // --- Deletion ---

    /**
     * @brief Delete a key from the subtree rooted at 'node'.
     * Handles standard BST deletion logic, then rebalances the tree.
     * @param node The subtree root from which to delete.
     * @param key The key to remove.
     * @return Node* The new root of the subtree after deletion.
     */
    Node* deleteNode(Node* node, int key);

    // --- Searching ---

    /**
     * @brief Search for a key in the subtree rooted at 'node'.
     * @param node The subtree root to search.
     * @param key The key to find.
     * @return true If the key is found.
     * @return false Otherwise.
     */
    bool searchNode(Node* node, int key);

    // --- Traversals ---

    /**
     * @brief Print an in-order traversal of the subtree rooted at 'node'.
     * This prints the keys in ascending order.
     * @param node The subtree root to traverse.
     */
    void inOrderTraversal(Node* node);

    // --- Clearing the Tree ---

    /**
     * @brief Clear all nodes from the subtree rooted at 'node'.
     * Recursively deletes all nodes in that subtree.
     * @param node The subtree root to clear.
     */
    void clearSubtree(Node* node);

    // --- Advanced Operations (Optional) ---

    /**
     * @brief Build a balanced AVL subtree from a sorted array of keys.
     * Useful for merging two AVL trees by merging their sorted keys.
     * @param keys A sorted array of keys.
     * @param start Start index in the array.
     * @param end End index in the array.
     * @return Node* The root of the balanced subtree.
     */
    Node* buildAVLFromSortedArray(const std::vector<int>& keys, int start, int end);

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
    int selectNode(Node* node, int i);

    /**
     * @brief Return the rank of a given key in the subtree rooted at 'node'.
     * Rank is the position of the key in sorted order (1-based).
     * @param node Subtree root.
     * @param key The key whose rank is desired.
     * @return int The rank of the key; 0 if not found.
     */
    int rankOfKey(Node* node, int key);

public:
    /**
     * @brief Construct an empty AVLTree.
     */
    AVLTree();

    /**
     * @brief Insert a key into the AVL tree.
     * @param key The key to insert.
     */
    void insert(int key);

    /**
     * @brief Remove a key from the AVL tree.
     * @param key The key to remove.
     */
    void remove(int key);

    /**
     * @brief Check if a key is present in the AVL tree.
     * @param key The key to search for.
     * @return true If the key is found.
     * @return false Otherwise.
     */
    bool search(int key);

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
    int rank(int key);
};
