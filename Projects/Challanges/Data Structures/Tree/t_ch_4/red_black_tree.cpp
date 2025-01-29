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

            if (aunt && aunt->isRed) {
                recolorNodes(node, aunt);
                node = node->parent->parent;
            } else {
                if (node->parent == node->parent->parent->left) {
                    if (node == node->parent->right) {
                        leftRotate(node->parent);
                        node = node->left;
                    }
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rightRotate(node->parent->parent);
                } else {
                    if (node == node->parent->left) {
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
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void fixDelete(Node* node) {
        while (node != root && !node->isRed) {
            bool isLeftChild = (node == node->parent->left);
            Node* sibling = isLeftChild ? node->parent->right : node->parent->left;

            if (sibling->isRed) {
                sibling->isRed = false;
                node->parent->isRed = true;
                if (isLeftChild) {
                    leftRotate(node->parent);
                } else {
                    rightRotate(node->parent);
                }
                sibling = isLeftChild ? node->parent->right : node->parent->left;
            }

            if (!sibling->left->isRed && !sibling->right->isRed) {
                sibling->isRed = true;
                node = node->parent;
            } else {
                if (isLeftChild ? !sibling->right->isRed : !sibling->left->isRed) {
                    if (isLeftChild) {
                        sibling->left->isRed = false;
                        sibling->isRed = true;
                        rightRotate(sibling);
                    } else {
                        sibling->right->isRed = false;
                        sibling->isRed = true;
                        leftRotate(sibling);
                    }
                    sibling = isLeftChild ? node->parent->right : node->parent->left;
                }

                sibling->isRed = node->parent->isRed;
                node->parent->isRed = false;
                if (isLeftChild) {
                    sibling->right->isRed = false;
                    leftRotate(node->parent);
                } else {
                    sibling->left->isRed = false;
                    rightRotate(node->parent);
                }
                node = root;
            }
        }
        node->isRed = false;
    }

    void deleteNode(Node* target) {
        Node* y = target;
        Node* x;
        bool yOriginalColor = y->isRed;

        if (target->left == NIL) {
            x = target->right;
            transplant(target, target->right);
        } else if (target->right == NIL) {
            x = target->left;
            transplant(target, target->left);
        } else {
            y = findMin(target->right);
            yOriginalColor = y->isRed;
            x = y->right;
            if (y->parent == target) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = target->right;
                y->right->parent = y;
            }
            transplant(target, y);
            y->left = target->left;
            y->left->parent = y;
            y->isRed = target->isRed;
        }

        if (!yOriginalColor) {
            fixDelete(x);
        }
    }

    void clearSubtree(Node* node) {
        if (node != NIL) {
            clearSubtree(node->left);
            clearSubtree(node->right);
            delete node;
        }
    }

    void printInOrder(Node* node) {
        if (node != NIL) {
            printInOrder(node->left);
            cout << "(" << node->key << ", " << node->value << ") ";
            printInOrder(node->right);
        }
    }

    bool search(Node* node, K key) {
        if (node == NIL || key == node->key) {
            return node != NIL;
        }
        if (key < node->key) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
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
            } else {
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
        Node* node = root;
        while (node != NIL && node->key != key) {
            if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        if (node != NIL) {
            deleteNode(node);
        }
    }

    bool search(K key) {
        return search(root, key);
    }

    void printInOrder() {
        printInOrder(root);
        cout << endl;
    }

    void clear() {
        clearSubtree(root);
        root = NIL;
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
