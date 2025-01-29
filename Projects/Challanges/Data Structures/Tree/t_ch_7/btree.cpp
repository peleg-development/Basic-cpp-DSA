#include <iostream>
#include <vector>
#include <string>

/*
 * Btree of order m is in short a tree where every node can have at most m children and can store at most m-1 keys
 *
 * Now because a single node can store multiple keys and in order to respect the smaller greater
 * property then any child node sitting between any two keys should only contain key values that are greater
 * than their preceding key and smaller than their following key
 *
 * the elements stored inside the same node should be sorted in ascending order so the smallest element is stored at the left and the biggest at the right
 *
 * Inorder for a tree to be declared as a valid B-Tree of order m it should satisfy three additional properties:
 * 1. with the exception of the root, every non-leaf node (also known as internal nodes) should have at least [m/2] (ceiling of m over two) child nodes
 *    each of the internal nodes has at least 2 children 2 being the ceiling of 3/2 : [m/2]
 *    the reason behind this property lies within one of the main features of a B-Tree the height shrinking
 *    the ceiling of m over two property ensures that each internal node is at least half full
 *    and this relation implies that two half full nodes can be joined to make a legal node
 *    and that one full node can be split into two legal nodes
 *
 * 2. if a non-leaf node has n children then it must contain n-1 keys or values
 *    for example [10,         20           , 30]
 *          [2, 8]    [13, 17]    [24, 26]      [32, 36, 40]
 *    and consider that its root node has 4 children nodes
 *    if the root node didnt contain 3 elements you see 10, 20, 30
 *    how would we know that the elements stored in the first child should be smaller than 10
 *    the ones in the second child should be between 10 and 20 etc.
 *    so we have four children the parent node must have three elements or keys stored inside it
 *    or more generally if we have n children then the parent must have n-1 keys stored inside it
 *
 * 3. the last property a tree should satisfy in order to be a valid B-Tree is that
 *    all its leaf nodes should appear at the same level of the tree
 *    and if u think about it that is ind understandable given that a B-Tree is a self-balancing tree
 *    and that its ultimate goal it to reduce its height in order to speed up the operations we are allowed to execute
 *
 * Insertion:
 * Tree:
 *                  [12,                  17]
 *        [2 ,   8]            [15]             [20]
 *    [1]   [4,6]   [10]    [13]   [16]    [18]      [22, 25]
 *
 *    the btree is of order 3 also known as 2-3 B-Tree
 *
 *    now consider we want to insert the element 28 into this tree
 *    if we start at the root and hop to the left when 28 is bigger than the node we are standing at
 * Tree:
 *                  [12,                  17] ->
 *        [2 ,   8]            [15]             [20] ->
 *    [1]   [4,6]   [10]    [13]   [16]    [18]      [22, 25, 28]
 *
 *   Then 28 should be there but the maximum number of keys each node is allowed to hold is 2 since its of order 3
 *   "Btree of order m is in short a tree where every node can have at most m children and can store at most m-1 keys"
 *   so we split the node into 2 nodes and promote element 25 which is the middle element to the parent node
 *   in our case the parent node only contains a single child and has room for the element
 *                  [12,                  17]
 *        [2 ,   8]            [15]             [20]      <-
 *    [1]   [4,6]   [10]    [13]   [16]    [18]      [22]  [25, 28]
 *  -------------------------------------------------------------------
 *                  [12,                  17]
 *        [2 ,   8]            [15]             [20,    25]
 *    [1]   [4,6]   [10]    [13]   [16]    [18]     [22]   [28]
 *
 *  if the parent didnt have space for the 25 ( had already m - 1 elements inside it )
 *  then both the splitting and promoting actions should keep going all the way up till we reach the root node
 *                  [12,                  17]
 *        [2 ,   8]            [15]             [20,    25]
 *    [1]   [4,6]   [10]    [13]   [16]    [18]     [22]   [28]
 *
 *  take another element for example 3 if we insert 3 normally it will fit here
 *              <-  [12,                       17]
 *        [2 ,   8]                [15]             [20,    25]
 *    [1]   [3,4,6]   [10]      [13]   [16]    [18]     [22]   [28]
 *
 *    and as we did before and because this node already contains 2 elements two being m-1
 *    then we have to split it and promote its middle element to the parent node
 *                 [12,                  17]
 *        [2 ,  4,    8]            [15]             [20,    25]
 *    [1]    [3]  [6]   [10]    [13]   [16]    [18]     [22]   [28]
 *
 *    the middle element is 4 however here the parent already contains two elements
 *    so what we do now is split the parent node as well and promote its middle item to the root
 *                 [4    ,     12,            17]
 *        [2]        [8]            [15]             [20,    25]
 *    [1]    [3]  [6]   [10]    [13]   [16]    [18]     [22]   [28]
 *
 *    oh but the root is full as well so what we do is split the current root node then promote its middle
 *    element to a new node which will be the new root of the tree after doing this that is the final tree we obtain
 *                          [12]
 *              [4]                         [17]
 *        [2]        [8]            [15]             [20,    25]
 *    [1]    [3]  [6]   [10]    [13]   [16]    [18]     [22]   [28]
 *
 *    notice how this tree preserves all the B-Tree conditions
 *
 * Deletions:
 *                               [15]
 *              [2       ,8]                [24]
 *          [1]    [4,6]    [10]    [18,20]      [26, 30]
 *
 *    suppose we want to delete 30, 30 is inside a leaf node
 *    so we can go ahead and just remove it:
 *                               [15]
 *              [2       ,8]                [24]
 *          [1]    [4,6]    [10]    [18,20]      [26]
 *
 *    but what if we also want to delete 26 from the the tree
 *    it is also inside a leaf node and we can remove it directly
 *    however if we do that our tree will not be valid anymore and its parent node wont have the minimum number of required children
 *    so because it is a leaf node we have to remove it just like we did for the previous element
 *                               [15]
 *              [2       ,8]                [24]
 *          [1]    [4,6]    [10]    [18,20]
 *
 *    but after removing it what we have to do is balance our B-Tree to bring all the leaf nodes to the same level
 *    we balance a B-Tree with the help of rotations to fix this tree we need to look at the immediate siblings of the node we removed
 *    and if one of these siblings contains more than the minimum number of required elements which is the ceiling of m over 2
 *    then we can use left or right rotation
 *
 *    in our case the left sibling of the removed node contains two elements which is the maximum there for we can balance using right rotation
 *    the rotation is done by copying the separator or the middle element from the parent to a new node to its right
 *    so in other terms the separator moves down to ensure that the new node has the minimum number of elements
 *                               [15]
 *              [2       ,8]                ->
 *          [1]    [4,6]    [10]    [18,20]    [24]
 *
 *    then we have to replace the moved separator in the parents with the last element of the left sibling
 *                               [15]
 *              [2       ,8]                [20]
 *          [1]    [4,6]    [10]       [18]     [24]
 *
 *    the left sibling loses one node but still has at least the minimum number of required elements
 *
 * Another Case: where the right sibling is the one from which we can borrow elements
 *                               [15]
 *              [2       ,8]                [20]
 *          [1]    [4,6]    [10]       [18]     [24]
 *
 *    if we delete 1 well have to borrow from the node between 2 and 8 since its the immediate sibling
 *    if we do this we can rebalance our tree using a left rotation
 *                               [15]
 *              [2       ,8]                [20]
 *                 [4,6]    [10]       [18]     [24]
 *  -------------------------------------------------------------------
 *                               [15]
 *                [4,    8]                 [20]
 *           [2]     [6]    [10]       [18]     [24]
 *
 *    we moved 2 down and replaced it with the first element of the immediate sibling
 *
 * Now what if both the left and right sibling contained the minimum number of elements what are we going to put instead of the node we removed?
 *                               [15]
 *                [4,    8]                 [20]
 *           [2]     [6]    [10]       [18]     [24]
 *
 *    take element 6 for example if we remove this element from the tree we will encounter the scenario i was just mentioning
 *    to balance this tree again we have to merge the children of the parent of the node we just deleted
 *                               [15]
 *                [4,    8]                [20]
 *           [2]           [10]       [18]     [24]
 *
 *    to do this we have to copy the middle element of the parent to the end of the left node
 *                          [15]
 *                [4]                        [20]
 *           [2]      [8]   [10]        [18]     [24]
 *
 *    and here we dont care if this node is a newly created node as we have here or a sibling node with the minimum number of elements
 *    so we can copy the middle element to the beginning of the right node as well
 *
 *    Then what we have to do is move all the elements of the right node in this example to the left node
 *                          [15]
 *                [4]                     [20]
 *           [2]      [8, 10]        [18]     [24]
 *
 *    so the left node has now the maximum number of elements and the right node is empty, the parent just lost an element
 *    and the tree is now balanced.
 *
 * Deleting non-leaf nodes:
 *                          [15]
 *                [4]                     [20]
 *           [2]      [8, 10]        [18]     [24]
 *
 *    for example node 4 this node acts as a separation value for its two children sub-trees
 *    Therefore what we need to do is find a replacement for this separation
 *    this replacement can either be the largest element in the left node or the smallest element in the right node
 *                          [15]
 *                [2]                     [20]
 *                    [8, 10]        [18]     [24]
 *
 *    now we found our self's in a situation similar to the cases covered before
 *    because if you think about it what we just did is similar to removing an item from a leaf node
 *    so we just balance the tree notice that the immediate right sibling fo the empty node is full
 *    therefore we can balance this tree using a left rotation
 *                          [15]
 *                [8]                   [20]
 *           [2]       [10]        [18]     [24]
 *
 *    this rotation si done by brining up the first element of the right sibling to the parent to act as the middle item
 *    and by brining down the old separator of the parent to the end of its left child
 *
 * Searching for an element:
 *
 *
 * */

using namespace std;

//The factor of 2 comes from the maximum size of a node being roughly twice the minimum size (i.e., each node can hold between t−1t−1 and 2t−12t−1 keys).
//Therefore, the vector for keys and values must reserve space for up to 2t−12t−1 slots, and the vector for children must reserve up to 2t2t slots.

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
        // 1) Grab the child that’s full
        BTreeNode* fullChild = parentNode->children[childIndex];

        // 2) Create a new node to hold the upper (t - 1) keys of fullChild
        BTreeNode* newNode = new BTreeNode(fullChild->isLeaf, t);

        // 'mid' is the index of the key that will move up to the parent.
        // Typically, we promote the (t-1)-th key (0-based index).
        int mid = t - 1;

        // 3) Copy the top (t - 1) keys and values from fullChild into newNode
        //    These are the keys after the median.
        for (int i = 0; i < mid; i++) {
            newNode->keys[i]   = fullChild->keys[i + t];
            newNode->values[i] = fullChild->values[i + t];
        }

        // If the child is not a leaf, copy its top 't' children as well
        if (!fullChild->isLeaf) {
            for (int i = 0; i < t; i++) {
                newNode->children[i] = fullChild->children[i + t];
            }
        }

        // 4) Update the numKeys in the new node
        newNode->numKeys = mid;

        // 5) Reduce the key count in the fullChild (it loses the top half)
        fullChild->numKeys = mid;
        // After the split, 'fullChild' keeps [0..(mid-1)] of its keys.
        // The median key at index 'mid' will move up to the parent.

        // -----------------------------------------------------------------
        // Move parent’s children to make space for the new child
        // (We shift everything right by 1 from the back)
        // -----------------------------------------------------------------
        for (int i = parentNode->numKeys; i > childIndex; i--) {
            parentNode->children[i + 1] = parentNode->children[i];
        }
        parentNode->children[childIndex + 1] = newNode;

        // -----------------------------------------------------------------
        // Move parent’s keys/values to make space for the median key
        // (Shift them right by 1 from the back)
        // -----------------------------------------------------------------
        for (int i = parentNode->numKeys - 1; i > childIndex - 1; i--) {
            parentNode->keys[i + 1]   = parentNode->keys[i];
            parentNode->values[i + 1] = parentNode->values[i];
        }

        // 6) The median key of fullChild moves up to parent
        parentNode->keys[childIndex]   = fullChild->keys[mid];
        parentNode->values[childIndex] = fullChild->values[mid];

        // 7) The parent now has one more key
        parentNode->numKeys++;
    }

    /**
     * @brief Inserts a key-value pair into a non-full node of the B-Tree.
     *
     * @param node The current node where the key is being inserted. This changes as we descend the tree.
     * @param key The key to insert.
     * @param value The value to insert.
    */
    void insertNonFull(BTreeNode* node, const K& key, const V& value) {
        // TODO: Implement insertion logic:
        // 1) If node is a leaf, insert key/value in sorted position among existing keys.
        // 2) If node is not a leaf, find the correct child to descend into; if that child is full, split it first, then descend again.
        if (node->isLeaf) {
            int i = node->numKeys - 1;

            // Shift to the right until we find the position
            while (i >= 0 && node->keys[i] > key) {
                node->keys[i + 1]   = node->keys[i];
                node->values[i + 1] = node->values[i];
                i--;
            }

            // Now 'i' is either -1 or points to a key <= 'key'
            node->keys[i + 1]   = key;
            node->values[i + 1] = value;
            node->numKeys++;
        } else {
            // Start from the rightmost key in the node.
            int i = node->numKeys - 1;

            //

            // Move i leftward while the new key is smaller than node->keys[i].
            // That means we haven't found the correct "range" yet.
            while (i >= 0 && key < node->keys[i]) {
                i--;
            }

            // Now we've found where K fits among the node's keys.
            // The child pointer we descend into is at index (i + 1).
            int childIndex = i + 1;

            // If that child is full, we split it first.
            if (node->children[childIndex]->numKeys == (2*t - 1)) {
                splitChild(node, childIndex);

                // After splitting, one key moves up to the parent,
                // and the original child is cut in half. We decide
                // whether to go left or right.
                if (key > node->keys[childIndex]) {
                    childIndex++;
                }
            }

            // Finally, we insert into that child (recursively).
            insertNonFull(node->children[childIndex], key, value);
        }
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
    * Steps:
        *  1) If the root is null, create a new leaf root (store key/value).
        *  2) If the root is full, split it first.
            *     - Create a new node as the parent of the old root.
            *     - Call splitChild(newRoot, 0).
            *     - Decide if we go left or right child for the insertion.
     *  3) Otherwise, just call insertNonFull on the existing root.
    */
    void insert(const K& key, const V& value) {
        // 1) If the tree is empty (root == nullptr):
        if (root == nullptr) {
            // Create a new root node as a leaf
            root = new BTreeNode(true, t); // (isLeaf=true, t=degree)
            root->keys[0] = key;
            root->values[0] = value;
            root->numKeys = 1;
            return; // Done
        }

        // 2) If the root is full (has 2t - 1 keys), split it before descending
        if (root->numKeys == (2 * t - 1)) {
            // Create a new node to become the new root (this new root is not a leaf)
            BTreeNode* newRoot = new BTreeNode(false, t);

            // The old root becomes newRoot->children[0]
            newRoot->children[0] = root;

            // Split the old root (child at index 0 of newRoot)
            splitChild(newRoot, 0);

            // Now decide which child to descend into based on the key
            int childIndex = 0;
            if (key > newRoot->keys[0]) {
                childIndex = 1;
            }

            // Insert the key into the appropriate child
            insertNonFull(newRoot->children[childIndex], key, value);

            // newRoot is our actual root now
            root = newRoot;
        }
        else {
            // 3) If root is not full, just insert into it
            insertNonFull(root, key, value);
        }
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
