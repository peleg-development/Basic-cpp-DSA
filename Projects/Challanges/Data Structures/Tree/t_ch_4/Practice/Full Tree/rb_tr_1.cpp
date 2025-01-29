#include <iostream>
using namespace std;

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
    Node* NIL;
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
        } else if (oldRoot->parent->right == oldRoot) {
            oldRoot->parent->right = newRoot;
        } else {
            oldRoot->parent->left = newRoot;
        }
    }

    void leftRotate(Node* oldRoot) {
        Node* newRoot = oldRoot->right;
        Node* newRootLeft = newRoot->left;

        oldRoot->right = newRootLeft;
        if (newRootLeft != NIL) {
            newRootLeft->parent = oldRoot;
        }

        updateParents(oldRoot, newRoot);

        newRoot->left = oldRoot;
        oldRoot->parent = newRoot;
    }

    void rightRotate(Node* oldRoot) {
        Node* newRoot = oldRoot->left;
        Node* newRootRight = newRoot->right;

        oldRoot->left = newRootRight;
        if (newRootRight != NIL) {
            newRootRight->parent = oldRoot;
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

        if (node->parent == node->parent->parent->right) {
            return node->parent->parent->left;
        } else {
            return node->parent->parent->right;
        }
    }

    void fixInsert(Node* node) {
        while (node->parent && node->parent->isRed) {
            Node* aunt = getAunt(node);

            if (aunt && aunt->isRed) {
                recolorNodes(node, aunt);
                node = node->parent->parent;
            } else {
                if (node->parent->parent->left == node->parent) {
                    if (node == node->parent->right) {
                        leftRotate(node->parent);
                        node = node->left;
                    }

                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rightRotate(node->parent->parent);
                } else {
                    if (node->parent->left == node) {
                        rightRotate(node->parent);
                        node = node->right;
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
        if (node->left == nullptr) return node;
        findMin(node->left);
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
        while (node != root && !node->isRed) {
            bool isLeftChild = (node == node->parent->left);
            Node* sibling = (isLeftChild) ? node->parent->right : node->parent->left;

            if (sibling->isRed) {
                sibling->isRed = false;
                node->parent->isRed = true;
                if (isLeftChild) {
                    leftRotate(node->parent);
                } else {
                    rightRotate(node->parent);
                }
                sibling = (isLeftChild) ? node->parent->right : node->parent->left;
            }

            if (!sibling->right->isRed && !sibling->left->isRed) {
                sibling->isRed = true;
                node = node->parent;
            } else {
                if (isLeftChild ? !sibling->right->isRed : !sibling->left->isRed) {
                    if (isLeftChild) {
                        sibling->isRed = true;
                        rightRotate(sibling);
                    } else {
                        sibling->isRed = true;
                        leftRotate(sibling);
                    }
                    sibling = (isLeftChild) ? node->parent->right : node->parent->left;
                }

                sibling->isRed = node->parent->isRed;
                if (isLeftChild) {
                    sibling->right->isRed = false;
                    leftRotate(node->parent);
                } else {
                    sibling->left->isRed = false;
                    rightRotate(node->right);
                }
                root = node;
            }
        }
        node->isRed = false;
    }

    void deleteNode(Node* target) {
        Node* removedNode = target;
        bool removedNodeColor = target->isRed;
        Node* successor = nullptr;

        if (target->right == NIL) {
            successor = target->left;
            transplant(target, target->left);
        } else if (target->left == NIL) {
            successor = target->right;
            transplant(target, target->right);
        } else {
            Node* minNode = findMin(target->right);
            removedNodeColor = minNode->isRed;
            successor = minNode->right;

            if (minNode->parent == target) {
                successor->parent = minNode;
            } else {
                transplant(minNode, minNode->right);
                minNode->right = target->right;
                minNode->right->parent = minNode;
            }

            transplant(target, minNode);
            minNode->left = target->left;
            minNode->left->parent = minNode;
            minNode->isRed = target->isRed;
        }

        if (!removedNodeColor) {
            fixDelete(successor);
        }
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

    }

    void remove(K key) {

    }

    bool search(K key) {
        return search(root, key);
    }

    void printInOrder() {

    }

    void clear() {

    }
};

int main() {
    RedBlackTree<int, string> rbTree;

    rbTree.insert(10, "Ten");
    rbTree.insert(20, "Twenty");
    rbTree.insert(15, "Fifteen");

    cout << "In-order traversal after insertions: ";
    rbTree.printInOrder();

    cout << "\nSearching for 15: " << (rbTree.search(15) ? "Found" : "Not Found") << endl;

    rbTree.remove(15);
    cout << "In-order traversal after deletion: ";
    rbTree.printInOrder();

    rbTree.clear();
    cout << "\nTree cleared." << endl;

    return 0;
}
