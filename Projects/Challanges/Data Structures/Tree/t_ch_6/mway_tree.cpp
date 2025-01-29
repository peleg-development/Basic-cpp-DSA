#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>  // for std::upper_bound

using namespace std;

/**
 * @brief MWayTree class
 *
 * An M-Way (B-Tree-like) Search Tree where each node can have up to 'M' children
 * and up to 'M-1' keys.
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
     * - A vector of child pointers
     * - A count of the current number of keys
     */
    struct MWayTreeNode {
        vector<K> keys;                  // Node's keys
        vector<V> values;                // Values associated with each key
        vector<MWayTreeNode*> children;  // Child pointers
        int numKeys;                     // Current number of keys stored in this node
        bool leaf;                       // True if this node is a leaf

        MWayTreeNode(int M, bool leafStatus) :
                keys(M - 1),
                values(M - 1),
                children(M, nullptr),
                numKeys(0),
                leaf(leafStatus)
        {}
    };

    MWayTreeNode* root;  // Pointer to the root of the M-Way Search Tree
    int M;               // Maximum number of children per node

    // ----------------------------------------------------------------------
    //  Internal (Private) B-Tree-like Utility Methods
    // ----------------------------------------------------------------------

    /**
     * @brief Splits the full child node `child` of `parent` at index `childIndex`.
     *
     * After splitting, the middle key in the child node moves up to the parent,
     * the child is reduced to half-full, and a new sibling node is created.
     */
    void splitChild(MWayTreeNode* parent, int childIndex) {
        MWayTreeNode* child = parent->children[childIndex];

        // Create new sibling node
        MWayTreeNode* sibling = new MWayTreeNode(M, child->leaf);

        int mid = (M - 1) / 2;  // Middle index

        // Move the last (M-1)/2 keys from child to sibling
        for(int i = 0; i < mid; ++i) {
            sibling->keys[i] = child->keys[i + mid + 1];
            sibling->values[i] = child->values[i + mid + 1];
        }

        // If child is not a leaf, move its children as well
        if(!child->leaf) {
            for(int i = 0; i <= mid; ++i) {
                sibling->children[i] = child->children[i + mid + 1];
            }
        }

        sibling->numKeys = mid;
        child->numKeys   = mid;

        // Insert sibling into parent->children
        for(int i = parent->numKeys; i >= childIndex + 1; --i) {
            parent->children[i + 1] = parent->children[i];
        }
        parent->children[childIndex + 1] = sibling;

        // Move the middle key of child up to the parent
        for(int i = parent->numKeys - 1; i >= childIndex; --i) {
            parent->keys[i + 1]   = parent->keys[i];
            parent->values[i + 1] = parent->values[i];
        }

        parent->keys[childIndex]   = child->keys[mid];
        parent->values[childIndex] = child->values[mid];

        parent->numKeys++;
    }

    /**
     * @brief Inserts key/value into the subtree rooted at `node`.
     *        Assumes `node` is **not full** upon entry.
     */
    void insertNonFull(MWayTreeNode* node, const K& key, const V& value) {
        int i = node->numKeys - 1;

        // If this is a leaf, insert the key here.
        if(node->leaf) {
            // Shift keys greater than 'key' to the right
            while(i >= 0 && key < node->keys[i]) {
                node->keys[i + 1]   = node->keys[i];
                node->values[i + 1] = node->values[i];
                i--;
            }
            // Insert new key
            node->keys[i + 1]   = key;
            node->values[i + 1] = value;
            node->numKeys++;
        } else {
            // Find the child where the key should be inserted
            while(i >= 0 && key < node->keys[i]) {
                i--;
            }
            i++;

            // If the child is full, split it first
            if(node->children[i]->numKeys == M - 1) {
                splitChild(node, i);

                // After splitting, decide which child to go down
                if(key > node->keys[i]) {
                    i++;
                }
            }
            insertNonFull(node->children[i], key, value);
        }
    }

    /**
     * @brief Recursively searches for `key` in the subtree rooted at `node`.
     * @return True if found, false otherwise.
     */
    bool searchNode(MWayTreeNode* node, const K& key) const {
        if(!node) return false;

        // 1) Find the first key >= key in this node
        int i = 0;
        while(i < node->numKeys && key > node->keys[i]) {
            i++;
        }

        // 2) If key == node->keys[i], we found it
        if(i < node->numKeys && key == node->keys[i]) {
            return true;
        }

        // 3) If leaf, it's not here
        if(node->leaf) {
            return false;
        }

        // 4) Otherwise, recurse into the child
        return searchNode(node->children[i], key);
    }

    /**
     * @brief Remove `key` from subtree rooted at `node` (very simplified).
     *
     * This does **not** fully handle borrowing/merging from siblings.
     * For demonstration only.
     */
    void removeNode(MWayTreeNode* node, const K& key) {
        if(!node) return;

        int i = 0;
        // Find the position of key in this node
        while(i < node->numKeys && key > node->keys[i]) {
            i++;
        }

        // Case 1: Key is found in this node
        if(i < node->numKeys && node->keys[i] == key) {
            // If leaf, just remove it
            if(node->leaf) {
                for(int j = i; j < node->numKeys - 1; ++j) {
                    node->keys[j]   = node->keys[j + 1];
                    node->values[j] = node->values[j + 1];
                }
                node->numKeys--;
            } else {
                // Internal node (very naive approach):
                // We'll replace with successor key from the next child,
                // then remove that key from the child.
                MWayTreeNode* cur = node->children[i + 1];
                // Find leftmost leaf in the right subtree
                while(!cur->leaf) {
                    cur = cur->children[0];
                }
                // Replace
                node->keys[i]   = cur->keys[0];
                node->values[i] = cur->values[0];
                // Remove from child
                removeNode(node->children[i + 1], cur->keys[0]);
            }
        }
        else {
            // Key not found in this node, so descend into the correct child
            if(node->leaf) {
                // Key not present
                return;
            }
            removeNode(node->children[i], key);
        }
    }

    /**
     * @brief Print in-order traversal of the subtree rooted at `node`.
     */
    void printInOrderNode(MWayTreeNode* node) const {
        if(!node) return;

        // For each key in the node, print left child, then the key, then move right
        for(int i = 0; i < node->numKeys; ++i) {
            printInOrderNode(node->children[i]);
            cout << node->keys[i] << " ";
        }
        // Print the last child
        printInOrderNode(node->children[node->numKeys]);
    }

    /**
     * @brief Deallocates memory for the subtree rooted at `node`.
     */
    void clearSubtree(MWayTreeNode* node) {
        if(!node) return;
        // Recursively clear all children
        for(int i = 0; i <= node->numKeys; ++i) {
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
        if(M < 2) {
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
     * Uses a B-Tree-like approach:
     * 1) If root is null, create a new root node and insert the key.
     * 2) If root is full, split it, then insert.
     * 3) Otherwise, insertNonFull.
     */
    void insert(const K& key, const V& value) {
        if(!root) {
            // Create root as a leaf
            root = new MWayTreeNode(M, true);
            root->keys[0]   = key;
            root->values[0] = value;
            root->numKeys   = 1;
        } else {
            // If root is full, split it
            if(root->numKeys == M - 1) {
                MWayTreeNode* newRoot = new MWayTreeNode(M, false);
                newRoot->children[0] = root;
                // Split the old root
                splitChild(newRoot, 0);
                // Decide which child to go down
                int i = 0;
                if(key > newRoot->keys[0]) {
                    i++;
                }
                insertNonFull(newRoot->children[i], key, value);
                root = newRoot;
            } else {
                // Root is not full, insert directly
                insertNonFull(root, key, value);
            }
        }
    }

    /**
     * @brief Search for a key in the M-Way Search Tree.
     *
     * @param key The key to search for.
     * @return bool True if key is found, false otherwise.
     */
    bool search(const K& key) const {
        return searchNode(root, key);
    }

    /**
     * @brief Remove a key from the M-Way Search Tree.
     *
     * This is a naive removal (does not merge or borrow from siblings).
     */
    void remove(const K& key) {
        if(!root) return;

        removeNode(root, key);

        // If after removal, the root has 0 keys, make its child the new root
        // (part of standard B-tree logic if the root becomes empty).
        if(root->numKeys == 0) {
            // If it has a child, use that child as root
            if(!root->leaf) {
                MWayTreeNode* temp = root;
                root = root->children[0];
                delete temp;
            }
                // Else, the tree is empty
            else {
                delete root;
                root = nullptr;
            }
        }
    }

    /**
     * @brief Print the M-Way Search Tree keys in sorted (in-order) order.
     */
    void printInOrder() const {
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
    MWayTree<int, string> mwayTree(3); // M = 3 => up to 2 keys per node

    mwayTree.insert(10, "Ten");
    mwayTree.insert(20, "Twenty");
    mwayTree.insert(5,  "Five");
    mwayTree.insert(6,  "Six");
    mwayTree.insert(12, "Twelve");
    mwayTree.insert(30, "Thirty");
    mwayTree.insert(7,  "Seven");
    mwayTree.insert(17, "Seventeen");

    cout << "In-order after multiple inserts:" << endl;
    mwayTree.printInOrder();
    // Example output (keys in sorted order): 5 6 7 10 12 17 20 30

    // Search test
    int searchKey = 20;
    if (mwayTree.search(searchKey)) {
        cout << searchKey << " found in M-Way Search Tree" << endl;
    } else {
        cout << searchKey << " not found in M-Way Search Tree" << endl;
    }

    // Remove test
    cout << "Removing 10, 6, 30..." << endl;
    mwayTree.remove(10);
    mwayTree.remove(6);
    mwayTree.remove(30);

    cout << "In-order after removals:" << endl;
    mwayTree.printInOrder();
    // Removal is naive; keys should be gone, but no merges are done

    return 0;
}
