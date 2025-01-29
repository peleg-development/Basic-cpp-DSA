#include <iostream>
#include <vector>

/**
 * @brief SplayTree class
 *
 * This class provides a skeleton for a generic Splay Tree,
 * which stores key-value pairs (K as key, V as value).
 *
 * Splay Trees work by "splaying" (bringing) the most recently accessed node
 * to the root via tree rotations, aiming to optimize for locality of access
 * over time.
 */

template <typename K, typename V>
class SplayTree {
private:
    /**
     * @brief A single node in the Splay Tree.
     *
     * Each node stores:
     * - A key (K)
     * - A value (V)
     * - Pointers to its parent, left child, and right child
     */
    struct Node {
        K key;          // Key stored in the node
        V value;        // Value associated with the key
        Node* parent;   // Pointer to parent node
        Node* left;     // Pointer to left child
        Node* right;    // Pointer to right child

        Node(const K& k, const V& v)
                : key(k), value(v), parent(nullptr), left(nullptr), right(nullptr) {}
    };

    Node* root; // The root node of the Splay Tree

    // --- Utility (Private) Methods ---

    /**
     * @brief Splay the given node to the root.
     *
     * This is the core of the Splay Tree operation. It uses
     * different rotation patterns (Zig, Zig-Zig, Zig-Zag) to
     * bring 'node' up to the root.
     *
     * @param node The node to splay.
     */
    void splay(Node* node);

    /**
     * @brief Perform a left rotation on the subtree rooted at 'x'.
     *
     * @param x The node on which to perform the rotation.
     */
    void rotateLeft(Node* x);

    /**
     * @brief Perform a right rotation on the subtree rooted at 'x'.
     *
     * @param x The node on which to perform the rotation.
     */
    void rotateRight(Node* x);

    /**
     * @brief Insert a new node into the BST (binary search tree) portion of the structure
     * (i.e., ignoring splay). This is typically followed by a splay operation.
     *
     * @param root The subtree root where insertion should happen.
     * @param node The new node to insert.
     * @return Node* The (possibly new) root of the subtree after insertion.
     */
    Node* bstInsert(Node* root, Node* node);

    /**
     * @brief Search for a key in the BST portion of the tree.
     *
     * This does NOT splay the found node automatically; typically, you'd call
     * 'splay' after finding the node.
     *
     * @param root The root of the subtree in which to search.
     * @param key The key to search for.
     * @return Node* The node containing the key if found, otherwise nullptr.
     */
    Node* bstSearch(Node* root, const K& key);

    /**
     * @brief Find the node with the minimum key in the subtree.
     *
     * @param node The subtree root.
     * @return Node* The minimum node in that subtree (or nullptr if empty).
     */
    Node* findMin(Node* node);

    /**
     * @brief Remove a node from the BST portion of the tree (without splay).
     * Usually, after removal, you'll decide what to splay (or if needed).
     *
     * @param root The root of the subtree.
     * @param key The key to remove.
     * @return Node* The new subtree root after removal.
     */
    Node* bstRemove(Node* root, const K& key);

    /**
     * @brief Utility to clear (delete) an entire subtree.
     *
     * @param node The root of the subtree to clear.
     */
    void clearSubtree(Node* node);

    /**
     * @brief Helper for in-order traversal printing.
     *
     * @param node The current node in the subtree.
     */
    void printInOrder(Node* node);

public:
    /**
     * @brief Construct an empty Splay Tree.
     */
    SplayTree();

    /**
     * @brief Destroy the Splay Tree, releasing all resources.
     */
    ~SplayTree();

    /**
     * @brief Insert a key-value pair into the Splay Tree.
     *
     * Typical steps:
     * 1) Insert as in a normal BST.
     * 2) Splay the inserted node to root.
     *
     * @param key The key to insert.
     * @param value The value associated with the key.
     */
    void insert(const K& key, const V& value);

    /**
     * @brief Search for a key in the Splay Tree.
     *
     * If found, splay the found node to root.
     * If not found, optionally splay the last accessed node (depends on your implementation).
     *
     * @param key The key to search for.
     * @return bool True if key is found, false otherwise.
     */
    bool search(const K& key);

    /**
     * @brief Remove a key from the Splay Tree.
     *
     * Steps can vary, but typically:
     * 1) Search for the key (which splays it to root if found).
     * 2) If found at root, remove it using normal BST logic + some splay strategy on remaining subtree.
     *
     * @param key The key to remove.
     */
    void remove(const K& key);

    /**
     * @brief Print the Splay Tree keys in ascending (in-order) order.
     */
    void printInOrder();

    /**
     * @brief Remove all nodes from the Splay Tree, making it empty.
     */
    void clear();
};

int main() {
    SplayTree<int, std::string> splayTree;
    splayTree.insert(10, "Ten");
    splayTree.insert(20, "Twenty");
    splayTree.insert(5, "Five");

    splayTree.printInOrder();

    splayTree.search(20); // Will splay "20" to the root

    splayTree.remove(10);

    splayTree.printInOrder();

    return 0;
}
