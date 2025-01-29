#include <iostream>
#include <stdexcept>
#include "../../../Queue/main.cpp"

using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};


class Tree {
private:
    TreeNode* root;

public:
    Tree(int root_value) {
        root = new TreeNode(root_value);
    }

    ~Tree() {
        delete root;
    }

    TreeNode* findParentTreeNode(int value, TreeNode* current_TreeNode) {
        while (current_TreeNode) {
            if (value < current_TreeNode->value) {
                if (!current_TreeNode->left) return current_TreeNode;
                current_TreeNode = current_TreeNode->left;
            } else {
                if (!current_TreeNode->right) return current_TreeNode;
                current_TreeNode = current_TreeNode->right;
            }
        }
        return nullptr;
    }

    void insert(int value) {
        if (!root) {
            root = new TreeNode(value);
            return;
        }

        TreeNode* parent = findParentTreeNode(value, root);

        if (value < parent->value) {
            parent->left = new TreeNode(value);
        } else {
            parent->right = new TreeNode(value);
        }
    }

    bool search(int value) {
        TreeNode* current = root;

        while (current) {
            if (value == current->value) {
                return true;
            }
            if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return false;
    }



    void remove(int value) {
        TreeNode* parent = findParentTreeNode(value, root);
        if (value < parent->value) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
    }

    int findMin();                  // Find the minimum value in the tree
    int findMax();                  // Find the maximum value in the tree
    int height();                   // Calculate the height of the tree
    void traverseInOrder();         // Traverse the tree in-order
    void traversePreOrder();        // Traverse the tree pre-order
    void traversePostOrder();       // Traverse the tree post-order

    // BFS USE
    void Bfs_printTree() {
        Queue<TreeNode*> queue;
        queue.enqueue(root);
        while (!queue.isEmpty()) {
            if (queue.front()->left != nullptr) {
                queue.enqueue(queue.front()->left);
            }
            if (queue.front()->right != nullptr) {
                queue.enqueue(queue.front()->right);
            }

            cout << queue.front()->value << " ";
            queue.dequeue();
        }
    }

    // Pre order
    void Dfs_1_printTree() {
        Dfs_1_printTree(root);
    }

    void Dfs_1_printTree(TreeNode* current_node) {
        cout << current_node->value << " ";
        if (current_node->left) {
            Dfs_1_printTree(current_node->left);
        }
        if (current_node->right) {
            Dfs_1_printTree(current_node->right);
        }
    }

    // Post order
    void Dfs_2_printTree() {
        Dfs_2_printTree(root);
    }

    void Dfs_2_printTree(TreeNode* current_node) {
        if (current_node == nullptr) {
            return;
        }

        Dfs_2_printTree(current_node->left);

        Dfs_2_printTree(current_node->right);

        cout << current_node->value << " ";
    }

    // In Order
    void Dfs_3_printTree() {
        Dfs_3_printTree(root);
    }

    void Dfs_3_printTree(TreeNode* current_node) {
        if (current_node == nullptr) {
            return;
        }

        Dfs_3_printTree(current_node->left);
        cout << current_node->value << " ";

        Dfs_3_printTree(current_node->right);
    }

};


int main() {
//    Queuetest();
    Tree tree(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    cout << "Tree traversal: (BFS)" << endl;
    tree.Bfs_printTree();
    cout << endl;

    cout << "Tree traversal: (DFS #1)" << endl;
    tree.Dfs_1_printTree();
    cout << endl;

    cout << "Tree traversal: (DFS #2)" << endl;
    tree.Dfs_2_printTree();
    cout << endl;

    cout << "Tree traversal: (DFS #3)" << endl;
    tree.Dfs_3_printTree();
    cout << endl;

    return 0;
}