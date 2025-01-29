#include <iostream>
#include <stdexcept>

using namespace std;

/*
About Red-Black Trees:

A Red-Black Tree is a self-balancing binary search tree that maintains a balanced height
through a set of color and structural properties, ensuring O(log n) time complexity for
insertion, deletion, and search operations.

Key Properties:
1. Each node is either red or black.
2. The root is always black.
3. No path has two consecutive red nodes (a red node cannot have a red parent).
4. Every path from the root to a leaf or null child has the same number of black nodes.

These rules maintain a roughly balanced tree, preventing worst-case skewed shapes.

Operations:
- Insertion:
  1) Insert the new node as you would in a regular binary search tree.
  2) Color the new node red.
  3) Fix any violations of the red-black properties by performing rotations and/or recoloring.
     - If a red child has a red parent, use rotations (left or right) and recolor nodes as needed.

- Deletion:
  1) Delete the node as in a regular binary search tree.
  2) If the deleted node or its replacement was black, fix potential property violations.
     - Perform rotations and recoloring to ensure black-height consistency.
     - If extra blackness arises (known as a "double black" scenario), propagate it upwards
       while applying rotations and recoloring to restore balanced properties.

- Searching:
  1) Similar to a regular binary search tree: follow left or right children based on key comparison.
  2) Balanced height ensures O(log n) search complexity.

Rotations:
- Left Rotation and Right Rotation are tree transformations used to rebalance the tree.
- A rotation pivots the tree around an edge between two nodes, adjusting their positions and
  subtree assignments.
- Rotations fix structural imbalances after insertions or deletions without violating the
  binary search property.

Recoloring:
- Change node colors from red to black or vice versa to maintain the black-height property.
- Typically done in conjunction with rotations when fixing rule violations after inserts/deletes.

Why Red-Black Trees?
- Ensures operations are O(log n) in worst case.
- Simpler to implement and reason about than some other self-balancing trees (like AVL trees).
- Widely used in standard library implementations (e.g., std::map).

In summary, Red-Black Trees ensure that paths from root to leaves are short and evenly balanced
in terms of black nodes, allowing balanced tree operations and maintaining efficiency for common operations.
*/

template <typename K, typename V>
class RedBlackTree {
public:
    struct Node {
        int key;
        Node* parent;     // Pointer to the parent node
        Node* left;       // Pointer to the left child node
        Node* right;      // Pointer to the right child node
        bool isRed;       // true if the node is red, false if black

        Node(int key)
                : key(key), parent(nullptr), left(nullptr), right(nullptr), isRed(true) {}
    };

private:
    Node* root;

    /**
     * rotateLeft(Node*&):
     * Performs a left rotation around the given node to restore the Red-Black Tree balance.
     * A left rotation moves the given node down to the left, and its right child becomes its parent.
     */
    void rotateLeft(Node*& node);

    /**
     * rotateRight(Node*&):
     * Performs a right rotation around the given node to restore the Red-Black Tree balance.
     * A right rotation moves the given node down to the right, and its left child becomes its parent.
     */
    void rotateRight(Node*& node);

    /**
     * fixInsertion(Node*&):
     * Called after inserting a new node to fix any violations of the Red-Black Tree properties.
     * Uses recoloring and/or rotations to restore the tree's balance.
     */
    void fixInsertion(Node*& node);

    /**
     * fixDeletion(Node*&):
     * Called after deleting a node to fix any violations of the Red-Black Tree properties.
     * Uses recoloring and/or rotations to restore the tree's balance.
     */
    void fixDeletion(Node*& node);

public:
    /**
     * RedBlackTree():
     * Constructor to initialize an empty Red-Black Tree.
     * Sets the root of the tree to nullptr.
     */
    RedBlackTree() : root(nullptr) {}

    /**
     * insert(int key):
     * Inserts a new key into the Red-Black Tree.
     * If the tree is empty, the new node becomes the root (and is colored black).
     * Otherwise, performs a standard binary search tree insertion and then calls fixInsertion().
     */
    void insert(int key);

    /**
     * remove(int key):
     * Removes a node with the given key from the Red-Black Tree.
     * If the node is found, performs standard binary search tree deletion, followed by fixDeletion().
     */
    void remove(int key);

    /**
     * search(int key):
     * Searches for a node with the given key in the tree.
     * Returns a pointer to the node if found, or nullptr if the key does not exist in the tree.
     */
    Node* search(int key);

    /**
     * printTree():
     * Prints the Red-Black Tree in a readable format.
     * Traverses the tree (e.g., in-order, pre-order) and displays keys along with their colors.
     * Useful for debugging and verifying the tree's structure.
     */
    void printTree();
};

void RT_test() {

}