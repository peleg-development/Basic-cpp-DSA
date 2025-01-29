#include<bits/stdc++.h>

using namespace std;

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
    Node* splay(Node* node) {
        if (!node) return nullptr;

        while (node->parent != nullptr) {
            Node* parent = node->parent;
            Node* grandparent = parent ? parent->parent : nullptr;

            if (!grandparent) {
                // Zig step
                if (node == parent->left) {
                    rotateRight(parent);
                } else {
                    rotateLeft(parent);
                }
            } else if (node == parent->left && parent == grandparent->left) {
                // Zig-Zig step
                rotateRight(grandparent);
                rotateRight(parent);
            } else if (node == parent->right && parent == grandparent->right) {
                // Zig-Zig step
                rotateLeft(grandparent);
                rotateLeft(parent);
            } else if (node == parent->right && parent == grandparent->left) {
                // Zig-Zag step
                rotateLeft(parent);
                rotateRight(grandparent);
            } else {
                // Zig-Zag step
                rotateRight(parent);
                rotateLeft(grandparent);
            }
        }

        root = node; // Update the root after splaying
        return node;
    }



    /**
     * @brief Update a node parents transplant it instead of another.
     *
     * @param oldRoot The old subtree root
     * @param newRoot The soon to become new root of the subtree
     */
    void updateParents(Node* oldRoot, Node* newRoot) {
        if (newRoot) {
            newRoot->parent = oldRoot->parent;
        }
        if (!oldRoot->parent) {
            root = newRoot;
        } else if (oldRoot == oldRoot->parent->left) {
            oldRoot->parent->left = newRoot;
        } else {
            oldRoot->parent->right = newRoot;
        }
    }

    /**
     * @brief Perform a left rotation on the subtree rooted at 'x'.
     *
     * @param x The node on which to perform the rotation.
     */
    void rotateLeft(Node* x) {
        Node* newRoot = x->right;
        if (!newRoot) return; // No rotation if there's no right child

        x->right = newRoot->left;
        if (newRoot->left) {
            newRoot->left->parent = x;
        }

        updateParents(x, newRoot);

        newRoot->left = x;
        x->parent = newRoot;
    }


    /**
     * @brief Perform a right rotation on the subtree rooted at 'x'.
     *
     * @param x The node on which to perform the rotation.
     */
    void rotateRight(Node* x) {
        Node* newRoot = x->left;
        if (!newRoot) return; // No rotation if there's no left child

        x->left = newRoot->right;
        if (newRoot->right) {
            newRoot->right->parent = x;
        }

        updateParents(x, newRoot);

        newRoot->right = x;
        x->parent = newRoot;
    }


    /**
     * @brief Insert a new node into the BST (binary search tree) portion of the structure
     * (i.e., ignoring splay). This is typically followed by a splay operation.
     *
     * @param root The subtree root where insertion should happen.
     * @param node The new node to insert.
     * @return Node* The node that was inserted or the existing node with the same key.
     */
    Node* bstInsert(Node* root, Node* node) {
        if (root == nullptr) {
            return node;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;

            if (node->key < current->key) {
                if (current->left == nullptr) {
                    current->left = node;
                    node->parent = current;
                    return node;
                }
                current = current->left;
            } else if (node->key > current->key) {
                if (current->right == nullptr) {
                    current->right = node;
                    node->parent = current;
                    return node;
                }
                current = current->right;
            } else {
                std::cout << "Duplicate key detected: " << node->key << ". Updating value." << std::endl;
                current->value = node->value;

                delete node;
                return current;
            }
        }

        return root; // Should never reach here
    }



    /**
     * @brief Search for a node with a given key in the BST.
     *
     * @param root The root of the subtree.
     * @param key The key to search for.
     * @return Node* The node with the matching key, or nullptr if not found.
     */
    Node* bstSearch(Node* root, const K& key) {
        if (!root || root->key == key) {
            return root;
        }
        if (key < root->key) {
            return bstSearch(root->left, key);
        } else {
            return bstSearch(root->right, key);
        }
    }

    /**
     * @brief Find the node with the minimum key in the subtree.
     *
     * @param node The subtree root.
     * @return Node* The minimum node in that subtree (or nullptr if empty).
     */
    Node* findMin(Node* node) {
        if (!node) return nullptr;

        while (node->left != nullptr) {
            node = node->left;
        }

        return node;
    }

    /**
     * @brief Remove a node from the BST portion of the tree (without splay).
     * Usually, after removal, you'll decide what to splay (or if needed).
     *
     * @param root The root of the subtree.
     * @param key The key to remove.
     * @return Node* The new subtree root after removal.
     */
    Node* bstRemove(Node* root, const K& key) {
        if (!root) return nullptr;

        if (key < root->key) {
            root->left = bstRemove(root->left, key);
            if (root->left) {
                root->left->parent = root;
            }
        } else if (key > root->key) {
            root->right = bstRemove(root->right, key);
            if (root->right) {
                root->right->parent = root;
            }
        } else {
            if (!root->left) {
                Node* rightChild = root->right;
                if (rightChild) {
                    rightChild->parent = root->parent;
                }
                delete root;
                return rightChild;
            } else if (!root->right) {
                Node* leftChild = root->left;
                if (leftChild) {
                    leftChild->parent = root->parent;
                }
                delete root;
                return leftChild;
            } else {
                Node* successor = findMin(root->right);
                root->key = successor->key;
                root->value = successor->value;
                root->right = bstRemove(root->right, successor->key);
                if (root->right) {
                    root->right->parent = root;
                }
            }
        }

        return root;
    }

    /**
     * @brief Utility to clear (delete) an entire subtree.
     *
     * @param node The root of the subtree to clear.
     */
    void clearSubtree(Node* node) {
        if (!node) return;

        clearSubtree(node->left);
        clearSubtree(node->right);

        delete node;
    }

    /**
     * @brief Helper for in-order traversal printing.
     *
     * @param node The current node in the subtree.
     */
    void printInOrder(Node* node) {
        if (!node) return;

        printInOrder(node->left);
        std::cout << node->key << " ";
        printInOrder(node->right);
    }


public:
    /**
     * @brief Construct a new SplayTree object.
     */
    SplayTree() : root(nullptr) {}

    /**
     * @brief Destroy the Splay Tree, releasing all resources.
     */
    ~SplayTree() {
        clearSubtree(root);
        root = nullptr; // Ensure root is set to nullptr after destruction
    }


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
    void insert(const K& key, const V& value) {
        Node* newNode = new Node(key, value);
        Node* insertedNode = bstInsert(root, newNode);
        root = splay(insertedNode);
    }

    /**
     * @brief Search for a key in the Splay Tree.
     *
     * If found, splay the found node to root.
     * If not found, optionally splay the last accessed node (depends on your implementation).
     *
     * @param key The key to search for.
     * @return bool True if key is found, false otherwise.
     */
    bool search(const K& key) {
        Node* node = bstSearch(root, key);
        if (node) {
            root = splay(node);
            return true;
        }
        return false;
    }

    /**
     * @brief Remove a key from the Splay Tree.
     *
     * Steps:
     * 1) Search for the key (which splays it to root if found).
     * 2) If found at root, remove it and adjust the tree.
     *
     * @param key The key to remove.
     */
    void remove(const K& key) {
        if (!search(key)) return;

        root = bstRemove(root, key);

        if (root) {
            root->parent = nullptr;
        }
    }

    /**
     * @brief Print the Splay Tree keys in ascending (in-order) order.
     */
    void printInOrder() {
        printInOrder(root);
        std::cout << std::endl;
    }

    /**
     * @brief Remove all nodes from the Splay Tree, making it empty.
     */
    void clear() {
        clearSubtree(root);
        root = nullptr; // Set root to nullptr after clearing
    }
};

int main() {
    SplayTree<int, std::string> splayTree;

    // Edge Case 1: Empty Tree
    splayTree.remove(10); // Removing from empty tree
    splayTree.search(10); // Searching in empty tree

    // Edge Case 2: Single Node
    splayTree.insert(5, "Five");
    splayTree.search(5); // Search single node
    splayTree.remove(5); // Remove the only node

    // Edge Case 3: Duplicate Key
    splayTree.insert(10, "Ten");
    splayTree.insert(10, "Updated Ten"); // Should update the value and splay the existing node

    // Verify update
    if (splayTree.search(10)) {
        cout << "After updating, key 10 has value: " << "Updated Ten" << endl;
    }

    // Edge Case 4: Removing Root
    splayTree.insert(15, "Fifteen");
    splayTree.remove(10); // Remove node with key 10, which is not the root
    // Now, 15 should be the root

    // Verify removal
    if (!splayTree.search(10)) {
        cout << "Key 10 successfully removed." << endl;
    }

    // Edge Case 5: Balanced Tree
    splayTree.insert(20, "Twenty");
    splayTree.insert(30, "Thirty");
    splayTree.search(20); // Bring 20 to the root
    splayTree.remove(30); // Remove leaf

    // Verify structure
    splayTree.printInOrder();

    // Edge Case 6: Stress Test
    for (int i = 1; i <= 1000; ++i) {
        splayTree.insert(i, "Value " + std::to_string(i));
    }
    for (int i = 1; i <= 1000; ++i) {
        if (!splayTree.search(i)) {
            cout << "Error: Key " << i << " not found during search." << endl;
        }
    }
    for (int i = 1000; i >= 1; --i) {
        splayTree.remove(i);
        if (splayTree.search(i)) {
            cout << "Error: Key " << i << " was not removed properly." << endl;
        }
    }

    splayTree.printInOrder();

    splayTree.clear();
    splayTree.printInOrder();

    return 0;
}
