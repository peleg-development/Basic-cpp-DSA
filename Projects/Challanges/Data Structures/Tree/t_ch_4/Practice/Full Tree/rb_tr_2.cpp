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
        NIL->right = NIL->left = nullptr;
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
        oldRoot->right = newRoot->left;

        if (oldRoot->right != NIL) {
            newRoot->left->parent = oldRoot;
        }

        updateParents(oldRoot, newRoot);

        oldRoot->parent = newRoot;
        newRoot->left = oldRoot;
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
        if (!node->parent || !node || !node->parent->parent) {
            return nullptr;
        }

        if (node->parent == node->parent->parent->left)
            return node->parent->parent->right;
        else
            return node->parent->parent->left;
    }

    void fixInsert(Node* node) {
        while (node->parent && node->parent->isRed) {
            Node* aunt = getAunt(node);

            if (aunt->isRed) {
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
        if (node->left == NIL) return node;
        findMin(node->left);
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->right) {
            u->parent->right = v;
        } else {
            u->parent->left = v;
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
        Node* node = target;
        Node* successor;
        bool nodeColor = target->isRed;

        if (target->right == NIL) {
            successor = target->left;
            transplant(target, successor);
        } else if (target->left == NIL) {
            successor = target->right;
            transplant(target, successor);
        } else {
            node = findMin(node->right);
            nodeColor = node->isRed;
            successor = node->right;

            if (target == node->parent) {
                successor->parent = node;
            } else {
                transplant(node, successor);
                node->right = target->right;
                target->right->parent = node;
            }

            transplant(target, node);
            node->left = target->left;
            target->left->parent = node;
            node->isRed = target->isRed;
        }

        if (!nodeColor) {
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
        Node* newNode = new Node(key, value);
        newNode->left = newNode->right = NIL;

        Node* current = root;
        Node* parent = nullptr;

        while (current != NIL) {
            parent = current;
            if (key > current->key) {
                current = current->right;
            } else if (key < current->key) {
                current = current->left;
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
        Node* current = root;
        while (current != NIL && current->key != key) {
            if (key > current->key) {
                current = current->right;
            } else if (key < current->key) {
                current = current->left;
            }
        }
        if (current != NIL) {
            deleteNode(current);
        }
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
