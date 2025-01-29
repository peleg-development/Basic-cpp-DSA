#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief MWayTree class
 *
 * An M-Way Search Tree where each node can have up to 'M' children and 'M-1' keys.
 * This skeleton outlines the structure and the primary methods you’d typically implement.
 */
template <typename K, typename V>
class MWayTree {
private:
    /**
     * @brief MWayTreeNode struct
     *
     * Each node stores:
     * - A vector of keys
     * - A vector of associated values
     * - A vector of child pointers (each child is another MWayTreeNode)
     * - A count of the current number of keys
     *
     * The children vector has a size of M, and keys and values vectors have a size of M - 1.
     */
    struct MWayTreeNode {
        vector<K> keys;                // Node's keys
        vector<V> values;              // Values associated with each key
        vector<MWayTreeNode*> children; // Child pointers
        int numKeys;                   // Current number of keys stored in this node

        MWayTreeNode(int M) : numKeys(0) {
            keys.resize(M - 1);
            values.resize(M - 1);
            children.resize(M, nullptr);
        }
    };

    MWayTreeNode* root; // Pointer to the root of the M-Way Search Tree
    int M;              // Maximum number of children per node

    // --- Utility (Private) Methods ---

    /**
     * @brief Inserts a key-value pair into the tree rooted at 'node'.
     * This method handles insertion into the node and splitting if necessary.
     *
     * @param node The current node.
     * @param key The key to insert.
     * @param value The value to insert.
     * @return MWayTreeNode* Updated node after insertion.
     */
    MWayTreeNode* insertNode(MWayTreeNode* node, const K& key, const V& value) {
        // TODO: Implement insertion logic:
        // 1) If node is a leaf, insert key/value in sorted position among existing keys.
        // 2) If node is internal, find the correct child to descend into.
        // 3) Handle node splitting if necessary (if the node overflows).
        return node;
    }

    /**
     * @brief Searches for a key in the subtree rooted at 'node'.
     *
     * @param node The root of the subtree in which to search.
     * @param key The key to search for.
     * @return bool True if key is found, false otherwise.
     */
    bool searchNode(MWayTreeNode* node, const K& key) {
        // TODO: Use the M-Way Search Tree search logic:
        // 1) Find the first key in 'node->keys' that is >= key.
        // 2) If that key == key, return true.
        // 3) If node is leaf, return false because key not found.
        // 4) Else, recursively search in the appropriate child.
        return false;
    }

    /**
     * @brief Removes a key from the subtree rooted at 'node'.
     *
     * @param node The subtree root from which to remove the key.
     * @param key The key to remove.
     * @return MWayTreeNode* Updated node after removal.
     */
    MWayTreeNode* removeNode(MWayTreeNode* node, const K& key) {
        // TODO: Implement removal logic:
        // 1) If key is found in node, remove it and adjust the tree accordingly.
        // 2) If node is internal, find the appropriate successor or predecessor to replace.
        // 3) If key is not in node, recurse into the appropriate child.
        return node;
    }

    /**
     * @brief Print in-order traversal of the keys in the subtree rooted at 'node'.
     *
     * @param node The subtree root.
     */
    void printInOrderNode(MWayTreeNode* node) {
        if (node == nullptr) return;

        // Traverse children and keys
        for (int i = 0; i < node->numKeys; ++i) {
            printInOrderNode(node->children[i]);
            cout << node->keys[i] << " ";
        }
        // Traverse the last child
        printInOrderNode(node->children[node->numKeys]);
    }

    /**
     * @brief Deallocates memory for the subtree rooted at 'node'.
     *
     * @param node The subtree root to clear.
     */
    void clearSubtree(MWayTreeNode* node) {
        if (node == nullptr) return;

        // Recursively clear all children
        for (int i = 0; i <= node->numKeys; ++i) {
            clearSubtree(node->children[i]);
        }
        delete node;
    }

public:
    /**
     * @brief Constructor for MWayTree.
     *
     * @param M The maximum number of children per node. Must be >= 2.
     */
    MWayTree(int M) : root(nullptr), M(M) {
        if (M < 2) {
            throw invalid_argument("M must be at least 2");
        }
    }

    /**
     * @brief Destructor for MWayTree. Deallocates all nodes.
     */
    ~MWayTree() {
        clear();
    }

    /**
     * @brief Insert a key-value pair into the M-Way Search Tree.
     *
     * @param key The key to insert.
     * @param value The value associated with the key.
     */
    void insert(const K& key, const V& value) {
        // TODO: Implement the public insert logic.
        // 1) If root is null, create a new root node and insert the key.
        // 2) Otherwise, call insertNode on root.
        // 3) Handle root splitting if necessary.
    }

    /**
     * @brief Search for a key in the M-Way Search Tree.
     *
     * @param key The key to search for.
     * @return bool True if key is found, false otherwise.
     */
    bool search(const K& key) {
        return searchNode(root, key);
    }

    /**
     * @brief Remove a key from the M-Way Search Tree.
     *
     * @param key The key to remove.
     */
    void remove(const K& key) {
        // TODO: Implement the public remove logic.
        // 1) If root is null, do nothing.
        // 2) Otherwise, call removeNode on root.
        // 3) Adjust root if necessary after removal.
    }

    /**
     * @brief Print the M-Way Search Tree keys in sorted (in-order) order.
     */
    void printInOrder() {
        printInOrderNode(root);
        cout << endl;
    }

    /**
     * @brief Remove all nodes from the M-Way Search Tree, making it empty.
     */
    void clear() {
        clearSubtree(root);
        root = nullptr;
    }
};

// --- Example usage (main) ---
int main() {
    MWayTree<int, string> mwayTree(3); // M = 3 (Each node can have up to 2 keys and 3 children)

    mwayTree.insert(10, "Ten");
    mwayTree.insert(20, "Twenty");
    mwayTree.insert(5, "Five");

    mwayTree.printInOrder(); // Skeleton: no real output until methods are implemented

    if (mwayTree.search(20)) {
        cout << "20 found in M-Way Search Tree" << endl;
    } else {
        cout << "20 not found in M-Way Search Tree" << endl;
    }

    mwayTree.remove(10);

    mwayTree.printInOrder();

    return 0;
}
