#include <iostream>
#include <vector>

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
private:
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

    Node* root; // The root node of the Red-Black Tree
    Node* NIL;  // Sentinel NIL node to represent all leaves

    // --- Utility Functions ---

    /**
     * @brief Left rotate the subtree rooted at 'node'.
     * This operation adjusts pointers to perform a left rotation.
     * @param node The node to rotate around.
     */
    void leftRotate(Node* node);

    /**
     * @brief Right rotate the subtree rooted at 'node'.
     * This operation adjusts pointers to perform a right rotation.
     * @param node The node to rotate around.
     */
    void rightRotate(Node* node);

    /**
     * @brief Fix the Red-Black Tree properties after an insertion.
     * Rebalances the tree by adjusting colors and performing rotations as needed.
     * @param node The newly inserted node.
     */
    void fixInsert(Node* node);

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
    /**
     * @brief Construct an empty Red-Black Tree.
     */
    RedBlackTree();

    /**
     * @brief Destroy the Red-Black Tree, releasing all resources.
     */
    ~RedBlackTree();

    /**
     * @brief Insert a key-value pair into the Red-Black Tree.
     * @param key The key to insert.
     * @param value The value associated with the key.
     */
    void insert(K key, V value);

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

