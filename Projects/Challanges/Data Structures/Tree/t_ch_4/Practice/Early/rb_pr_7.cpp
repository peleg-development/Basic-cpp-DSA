#include <iostream>
using namespace std;

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
    struct Node {
        K key;
        V value;
        bool isRed;
        Node* parent;
        Node* left;
        Node* right;

        Node(K k, V v)
                : key(k), value(v), isRed(true), parent(nullptr), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;
    Node* NIL;  // Sentinel node to represent all leaves
    int size;

    void initializeNIL() {
        NIL = new Node(K{}, V{});
        NIL->isRed = false;
        NIL->left = NIL->right = nullptr;
    }

    void updateParents(Node*& oldRoot, Node*& newRoot) {
        newRoot->parent = oldRoot->parent;
        if (oldRoot->parent == nullptr) {
            root = newRoot;
        } else if (oldRoot == oldRoot->parent->left) {
            oldRoot->parent->left = newRoot;
        } else {
            oldRoot->parent->right = newRoot;
        }
    }

    void leftRotate(Node* oldRoot) {
        Node* newRoot = oldRoot->right;
        oldRoot->right = newRoot->left;

        if (newRoot->left != NIL) {
            newRoot->left->parent = oldRoot;
        }

        updateParents(oldRoot, newRoot);

        newRoot->left = oldRoot;
        oldRoot->parent = newRoot;
    }

    void rightRotate(Node* oldRoot) {
        Node* newRoot = oldRoot->left;
        oldRoot->left = newRoot->right;

        if (newRoot->right != NIL) {
            newRoot->right->parent = oldRoot;
        }

        updateParents(oldRoot, newRoot);

        newRoot->right = oldRoot;
        oldRoot->parent = newRoot;
    }

    void recolorNodes(Node*& node, Node*& aunt) {
        node->parent->isRed = false;
        aunt->isRed = false;
        node->parent->parent->isRed = true;
    }

    Node* getAunt(const Node* node) {
        if (!node || !node->parent || !node->parent->parent) {
            return nullptr;
        }
        if (node->parent == node->parent->parent->left) {
            return node->parent->parent->right;
        } else {
            return node->parent->parent->left;
        }
    }

    void fixInsert(Node* node) {
        while (node->parent && node->parent->isRed) {
            Node* aunt = getAunt(node);

            if (aunt && aunt->isRed) {  // Recoloring
                recolorNodes(node, aunt);
                node = node->parent->parent;  // Move up the tree
            } else {  // Rotations
                if (node->parent == node->parent->parent->left) {
                    if (node == node->parent->right) {
                        leftRotate(node->parent);
                    }
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rightRotate(node->parent->parent);
                } else {
                    if (node == node->parent->left) {
                        rightRotate(node->parent);
                    }
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->isRed = false;
    }

    Node* findMin(Node* node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u->parent->right == u) {
            u->parent->right = v;
        } else {
            u->parent->left = v;
        }

        v->parent = u->parent;
    }

    void fixDelete(Node* node) {
        while (node != root && (node == nullptr || !node->isRed)) {
            if (node == node->parent->left) {
                // Node is the left child
                Node* sibling = node->parent->right;

                if (sibling->isRed) {
                    // **Case 1**: Sibling is red
                    // - Recolor sibling and parent
                    // - Perform left rotation on parent
                    sibling->isRed = false;
                    node->parent->isRed = true;
                    rotateLeft(node->parent);
                    sibling = node->parent->right; // Update sibling after rotation
                }

                // **Case 2**: Sibling's children are both black
                if ((sibling->left == nullptr || !sibling->left->isRed) &&
                    (sibling->right == nullptr || !sibling->right->isRed)) {
                    // Recolor sibling to red
                    sibling->isRed = true;
                    // Move up the tree
                    node = node->parent;
                }
                else {
                    // **Case 3**: Sibling's right child is black, left child is red
                    if (sibling->right == nullptr || !sibling->right->isRed) {
                        if (sibling->left != nullptr) {
                            sibling->left->isRed = false;
                        }
                        sibling->isRed = true;
                        rotateRight(sibling);
                        sibling = node->parent->right; // Update sibling after rotation
                    }

                    // **Case 4**: Sibling's right child is red
                    sibling->isRed = node->parent->isRed;
                    node->parent->isRed = false;
                    if (sibling->right != nullptr) {
                        sibling->right->isRed = false;
                    }
                    rotateLeft(node->parent);
                    node = root; // Exit loop
                }
            }
            else {
                // Node is the right child (mirror image of above)
                Node* sibling = node->parent->left;

                if (sibling->isRed) {
                    // **Case 1**: Sibling is red
                    sibling->isRed = false;
                    node->parent->isRed = true;
                    rotateRight(node->parent);
                    sibling = node->parent->left; // Update sibling after rotation
                }

                // **Case 2**: Sibling's children are both black
                if ((sibling->left == nullptr || !sibling->left->isRed) &&
                    (sibling->right == nullptr || !sibling->right->isRed)) {
                    // Recolor sibling to red
                    sibling->isRed = true;
                    // Move up the tree
                    node = node->parent;
                }
                else {
                    // **Case 3**: Sibling's left child is black, right child is red
                    if (sibling->left == nullptr || !sibling->left->isRed) {
                        if (sibling->right != nullptr) {
                            sibling->right->isRed = false;
                        }
                        sibling->isRed = true;
                        rotateLeft(sibling);
                        sibling = node->parent->left; // Update sibling after rotation
                    }

                    // **Case 4**: Sibling's left child is red
                    sibling->isRed = node->parent->isRed;
                    node->parent->isRed = false;
                    if (sibling->left != nullptr) {
                        sibling->left->isRed = false;
                    }
                    rotateRight(node->parent);
                    node = root; // Exit loop
                }
            }
        }

        if (node != nullptr) {
            node->isRed = false; // Ensure the root is black
        }
    }


    void deleteNode(Node* target) {
        Node* removedNode = target;
        bool removedNodeColor = target->isRed;
        Node* replacement = nullptr;

        if (target->right != nullptr && target->left == nullptr) {
            replacement = target->right;
            transplant(target, replacement);
        } else if (target->right == nullptr && target->left != nullptr) {
            replacement = target->left;
            transplant(target, replacement);
        } else {
            Node* successor = findMin(target->right);
            deleteSuccessor(target, successor, removedNode, removedNodeColor, replacement);
        }

        if (!removedNodeColor) {
            fixDelete(replacement);
        }
    }

    void deleteSuccessor(Node*& target, Node*& successor, Node*& removedNode, bool& removedNodeColor, Node*& replacement) {
        removedNode = successor;
        removedNodeColor = successor->isRed;

        replacement = successor->right;
        if (successor->parent != target) {
            transplant(successor, successor->right);
            successor->right = target->right;
            target->right->parent = successor;
        }
        transplant(target, successor);

        successor->left = target->left;
        target->left->parent = successor;
        successor->isRed = target->isRed;
    }


    void clearSubtree(Node* node) {

    }

    void printInOrder(Node* node) {

    }

    bool search(Node* node, K key) {

    }

public:
    RedBlackTree() : root(nullptr), size(0) {
        initializeNIL();
        root = NIL;
    }

    ~RedBlackTree() {
        clear();
        delete NIL;
    }

    void insert(K key, V value) {
        Node* newNode = new Node(key, value);
        newNode->left = newNode->right = NIL;

        Node* parent = nullptr;
        Node* current = root;

        while (current != NIL) {
            parent = current;
            if (key < current->key) {
                current = current->left;
            } else if (key > current->key) {
                current = current->right;
            } else {  // Duplicate keys not allowed
                delete newNode;
                return;
            }
        }

        newNode->parent = parent;
        if (parent == nullptr) {
            root = newNode;
        } else if (key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        fixInsert(newNode);
    }

    void remove(K key) {
        // Removal logic here (omitted for brevity)
    }

    bool search(K key) {
        return search(root, key);
    }

    void printInOrder() {
        printInOrder(root);
    }

    void clear() {
        clearSubtree(root);
        root = NIL;
    }
};

// Test cases in main.cpp
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

