#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief BTree class
 *
 * A B-Tree of minimum degree `t`. Each node can have up to `2t - 1` keys.
 * This skeleton outlines the structure and the primary methods you’d typically implement.
 */
template <typename K, typename V>
class BTree {
private:
    /**
     * @brief BTreeNode struct
     *
     * Each node stores:
     * - A vector of keys
     * - A vector of associated values (or you can store pairs if you prefer)
     * - A vector of child pointers (each child is another BTreeNode)
     * - A boolean flag to indicate if the node is a leaf
     * - A count of the current number of keys
     *
     * Note: In a typical B-Tree, the number of children is always (number_of_keys + 1),
     *       except for leaf nodes which have 0 children.
     */
    struct BTreeNode {
        bool isLeaf;                  // True if node is leaf
        vector<K> keys;         // Node's keys
        vector<V> values;       // Values associated with each key
        vector<BTreeNode*> children; // Child pointers
        int numKeys;                 // Current number of keys stored in this node

        BTreeNode(bool leaf, int t) : isLeaf(leaf), numKeys(0) {
            keys.resize(2 * t - 1);
            values.resize(2 * t - 1);
            children.resize(2 * t);
        }
    };

    BTreeNode* root; // Pointer to the root of the B-Tree
    int t;           // Minimum degree (each node can have [t-1 .. 2t-1] keys, except possibly root)

    // --- Utility (Private) Methods ---

    /**
     * @brief Splits the child of 'parentNode' at index 'childIndex' when it is full.
     * This is a fundamental operation in B-Trees during insertion.
     *
     * @param parentNode The node that has a full child.
     * @param childIndex The index of the child to split.
     */
    void splitChild(BTreeNode* parentNode, int childIndex) {
        // TODO: Implement logic to:
        // 1) Create a new node to hold the upper half of the child's keys.
        // 2) Move keys (and values, and children if not leaf) from the full child into the new node.
        // 3) Insert the new node into parentNode->children.
        // 4) Adjust parentNode->keys and parentNode->values to include the median key/value.
        // 5) Update numKeys in parentNode and both child nodes.
    }

    /**
     * @brief Inserts a key-value pair into a non-full node of the B-Tree.
     * This is used internally by the public insert method.
     *
     * @param node The node that is guaranteed not to be full.
     * @param key The key to insert.
     * @param value The value to insert.
     */
    void insertNonFull(BTreeNode* node, const K& key, const V& value) {
        // TODO: Implement insertion logic:
        // 1) If node is a leaf, insert key/value in sorted position among existing keys.
        // 2) If node is not a leaf, find the correct child to descend into; if that child is full, split it first, then descend again.
    }

    /**
     * @brief Searches for a key in the subtree rooted at 'node'.
     *
     * @param node The root of the subtree in which to search.
     * @param key The key to search for.
     * @return bool True if key is found, false otherwise.
     */
    bool searchNode(BTreeNode* node, const K& key) {
        // TODO: Use the B-Tree search logic:
        // 1) Find the first key in 'node->keys' that is >= key.
        // 2) If that key == key, return true.
        // 3) If node is leaf, return false because key not found.
        // 4) Else, recursively search in the appropriate child.
        return false;
    }

    /**
     * @brief Removes a key from the subtree rooted at 'node'.
     *
     * @param node The subtree root in which to remove the key.
     * @param key The key to remove.
     */
    void removeNode(BTreeNode* node, const K& key) {
        // TODO: B-Tree removal can be done in multiple steps:
        // 1) If key is in node and node is a leaf, remove the key from node.
        // 2) If key is in node and node is internal, you can either:
        //    a) Replace the key with its predecessor/successor and recursively remove from child, OR
        //    b) Merge children if needed.
        // 3) If key is not in node, search the correct child and ensure that child has at least t keys (split/merge if needed).
    }

    /**
     * @brief Print in-order traversal of the keys in the subtree rooted at 'node'.
     *
     * @param node The subtree root.
     */
    void printInOrderNode(BTreeNode* node) {
        // For each key i in [0..numKeys-1]:
        //   1) Recursively print the subtree in children[i]
        //   2) Print key[i]
        //   3) (In a B-Tree, children.size() = numKeys + 1 for internal nodes)
        // Print the subtree in children[numKeys] at the end.
    }

    /**
     * @brief Deallocates memory for the subtree rooted at 'node'.
     *
     * @param node The subtree root to clear.
     */
    void clearSubtree(BTreeNode* node) {

    }

public:
    /**
     * @brief Constructor for BTree.
     *
     * @param t The minimum degree of the B-Tree. Must be >= 2 for a valid B-Tree.
     */
    BTree(int t) : root(nullptr), t(t) {
        // Usually, we initialize an empty tree with a single root node that is a leaf.
        // But you can also keep it as nullptr until the first insertion.
    }

    /**
     * @brief Destructor for BTree. Deallocates all nodes.
     */
    ~BTree() {
        clear();
    }

    /**
     * @brief Insert a key-value pair into the B-Tree.
     * 
     * Typical steps:
     * 1) If the root is nullptr, create a new leaf root.
     * 2) If the root is full, split it first, then call insertNonFull.
     * 3) Else, directly call insertNonFull on the root.
     *
     * @param key The key to insert.
     * @param value The value associated with the key.
     */
    void insert(const K& key, const V& value) {
        // TODO: Implement the public insert logic described above.
        // 1) If root is null, create a leaf node as root, store key & value.
        // 2) If root is full, split root, then decide which child to descend into.
        // 3) Use insertNonFull(...) to actually insert.
    }

    /**
     * @brief Search for a key in the B-Tree.
     *
     * @param key The key to search for.
     * @return bool True if key is found, false otherwise.
     */
    bool search(const K& key) {
        return searchNode(root, key);
    }

    /**
     * @brief Remove a key from the B-Tree.
     *
     * Typical steps:
     * 1) If key exists in root, remove it from the root using removeNode().
     * 2) If after removal, the root has 0 keys (and is not a leaf), make its first child the new root.
     *
     * @param key The key to remove.
     */
    void remove(const K& key) {
        // TODO: Implement the public remove logic.
        // 1) If root is null, do nothing.
        // 2) Otherwise, call removeNode on root.
        // 3) If root->numKeys == 0 and root is not leaf, make the first child the new root.
    }

    /**
     * @brief Print the B-Tree keys in sorted (in-order) order.
     */
    void printInOrder() {
        printInOrderNode(root);
        cout << endl;
    }

    /**
     * @brief Remove all nodes from the B-Tree, making it empty.
     */
    void clear() {
        clearSubtree(root);
        root = nullptr;
    }
};

// --- Example usage (main) ---
int main() {
    BTree<int, string> btree(2); // Minimum degree t = 2

    btree.insert(10, "Ten");
    btree.insert(20, "Twenty");
    btree.insert(5,  "Five");

    btree.printInOrder(); // Skeleton: no real output until methods are implemented

    if (btree.search(20)) {
        cout << "20 found in B-Tree" << endl;
    } else {
        cout << "20 not found in B-Tree" << endl;
    }

    btree.remove(10);

    btree.printInOrder();

    return 0;
}
