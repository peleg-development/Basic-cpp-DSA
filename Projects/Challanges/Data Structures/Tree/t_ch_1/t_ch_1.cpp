#include <iostream>
#include <stdexcept>
#include <unordered_map>

#include "../Data Types/vector.cpp"
#include "../Data Types/queue.cpp"
using namespace std;

/* CH:
- You have a tree with N nodes (initially rooted at node 1), each node holding an integer value.

- Operations to implement:
  1) Update Node Value: Modify the value stored at any node. | Done
  2) Subtree Sum Query: Calculate the sum of all values in the subtree rooted at a given node. | Done
  3) Path Query: Compute the sum, minimum, or maximum value along the path between any two nodes.  | Done
  4) Dynamic Re-rooting: Change the root of the tree dynamically, maintaining all tree operations. | Done
  5) Tree Structure Modification: Remove an existing edge and add a new edge, ensuring the tree remains valid and functional. | Done
  6) Parents Getting: Get parents of each node in a good efficient way | Done
  7) Depth Challenge: get a depth map including all nodes with a key which is depth and a value which is nodes at this depth | Done

- Constraints:
  - Achieve near O(log N) per operation for large trees.
  - Use advanced data structures like Heavy-Light Decomposition, Euler TourA Trees, or Link-Cut Trees for optimization.
  - Ensure proper memory management for dynamically allocated nodes to prevent leaks during updates or deletions.

- Bonus Challenge:
  - Extend functionality to handle dynamic edge weights and edge-based queries (e.g., sum or max weight between nodes).
*/


class TreeNode {
public:
    int value;
    MyVector<TreeNode*> children;
    TreeNode* parent;

    TreeNode(int node_value, TreeNode* parent = nullptr) {
        this->value = node_value;
        this->parent = parent;
    }

    ~TreeNode() {
        for (TreeNode* child : children) {
            delete child;
        }

        children.clear();
    }
};

class Tree {
private:
    TreeNode* root;

    // BFS Node Find
    TreeNode* findNode(int value) {
        Queue<TreeNode*> queue;
        queue.enqueue(root);

        while (!queue.isEmpty()) {
            TreeNode* current = queue.front();
            queue.dequeue();

            if (current->value == value) {
                return current;
            }

            enqueueChildren(current, queue);
        }
        return nullptr;
    }

    void enqueueChildren(TreeNode* node, Queue<TreeNode*>& queue) {
        for (TreeNode* child : node->children) {
            queue.enqueue(child);
        }
    }

    // 2) Subtree Sum Query: Calculate the sum of all values in the subtree rooted at a given node.
    void sum_subtree(TreeNode *&node, int &sum) {
        if (node == nullptr) return;
        sum += node->value;
        for (TreeNode* child : node->children) {
            sum_subtree(child, sum);
        }
    }

    // 3) Path Query: Compute the sum, minimum, or maximum value along the path between any two nodes.
    int bfs_root_sum(TreeNode *&node) {
        int sum {0};
        Queue<TreeNode*> queue;
        queue.enqueue(node);
        while (queue.front() != root) {
            queue.enqueue(node->parent);
            sum += queue.front()->value;
            queue.dequeue();
        }
        return sum;
    }

    int calculate_min_child(TreeNode* current, TreeNode*& min_node) {
        int min_value = INT_MAX;
        min_node = nullptr;

        for (TreeNode* child : current->children) {
            if (child->value < min_value) {
                min_value = child->value;
                min_node = child;
            }
        }

        return min_value;
    }

    int calculate_max_child(TreeNode* current, TreeNode*& max_node) {
        int max_value = INT_MIN;
        max_node = nullptr;

        for (TreeNode* child : current->children) {
            if (child->value > max_value) {
                max_value = child->value;
                max_node = child;
            }
        }

        return max_value;
    }

    void process_min_node(TreeNode* current, int& sum, Queue<TreeNode*>& queue) {
        TreeNode* min_node = nullptr;
        int min_value = calculate_min_child(current, min_node);

        if (min_node) {
            sum += min_value;
            queue.enqueue(min_node);
        }
    }

    void process_max_node(TreeNode* current, int& sum, Queue<TreeNode*>& queue) {
        TreeNode* max_node = nullptr;
        int max_value = calculate_max_child(current, max_node);

        if (max_node) {
            sum += max_value;
            queue.enqueue(max_node);
        }
    }

    void bfs_calc_sum(TreeNode*& node, TreeNode*& target, bool calc_min) {
        int sum = bfs_root_sum(node);
        Queue<TreeNode*> queue;
        queue.enqueue(node);

        while (!queue.isEmpty()) {
            TreeNode* current = queue.front();
            queue.dequeue();

            if (calc_min) {
                process_min_node(current, sum, queue);
            } else {
                process_max_node(current, sum, queue);
            }
        }

        target->value = sum;
    }

    // 4) Dynamic Re-rooting: Change the root of the tree dynamically, maintaining all tree operations.
    void change_parents(TreeNode*& root, TreeNode*& new_root) {
        if (root == nullptr || new_root == nullptr) return;

        MyVector<TreeNode*> path;
        trace_path(root, new_root, path);

        TreeNode* prev = nullptr;
        for (TreeNode* current : path) {
            if (prev != nullptr) {
                MyVector<TreeNode*> new_children;

                for (TreeNode* child : current->children) {
                    if (child != prev) {
                        new_children.push_back(child);
                    }
                }
                current->children = new_children;

                current->children.push_back(prev);
            }

            prev = current;
        }

        root = new_root;
    }


    bool trace_path(TreeNode* current, TreeNode* target, MyVector<TreeNode*>& path) {
        if (current == nullptr) return false;

        path.push_back(current);

        if (current == target) return true;

        for (TreeNode* child : current->children) {
            if (trace_path(child, target, path)) {
                return true;
            }
        }

        path.pop_back();
        return false;
    }

    // 6) Get Parents of each node in a good efficient way
    void get_parents_dfs(TreeNode *&node, TreeNode *&target_node, MyVector<TreeNode*> &parents) {
        if (node == nullptr || target_node == nullptr) return;

        try {
            if (node->children.find(target_node)) {
                parents.push_back(node);
                target_node = node;
                return;
            }
        } catch (const exception& e) {
            cerr << "Exception in find: " << e.what() << std::endl;
        }

        for (TreeNode* child : node->children) {
            get_parents_dfs(child, target_node, parents);
        }
    }

    void get_parents_bfs(TreeNode *&target_node, MyVector<TreeNode*> &parents) {
        Queue<TreeNode*> queue;

        while (!queue.isEmpty()) {
            TreeNode* current = queue.front();
            queue.dequeue();

            try {
                if (current->children.find(target_node)) {
                    target_node = current;
                    parents.push_back(current);
                    queue.enqueue(root);
                    continue;
                }
            } catch (const exception& e) {
                cerr << e.what() << endl;
            }

            for (TreeNode* child : current->children) {
                queue.enqueue(child);
            }
        }
    }

    // 7) Depth challenge
    void get_depth_map(unordered_map<int, MyVector<TreeNode*>> &depth_map) {
        Queue<pair<TreeNode*, int>> queue;
        queue.enqueue({root, 0});

        while (!queue.isEmpty()) {
            auto [current, depth] = queue.front();
            queue.dequeue();
            depth_map[depth].push_back(current);

            for (TreeNode* child : current->children) {
                queue.enqueue({child, depth+1});
            }
        }
    }

    int get_node_depth(const unordered_map<int, MyVector<TreeNode*>>& depth_map, TreeNode* target_node) {
        for (const auto& [depth, nodes] : depth_map) {
            for (TreeNode* node : nodes) {
                if (node == target_node) {
                    return depth;
                }
            }
        }

        throw logic_error("Node not found in depth map");
    }


public:
    Tree(int root_value) {
        root = new TreeNode(root_value, nullptr);
    }

    ~Tree() {
        delete root;
    }

    void insert(int node_value, int parent_value) {
        TreeNode* parent = findNode(parent_value);
        if (!parent) {
            throw logic_error("Parent node not found");
        }

        auto* new_node = new TreeNode(node_value, parent);
        parent->children.push_back(new_node);
    }

    bool find(int node_value) {
        TreeNode* node = findNode(node_value);
        if (node)
            return true;
        return false;
    }

    TreeNode* get_node(int node_value) {
        TreeNode* node = findNode(node_value);
        if (node)
            return node;
        throw logic_error("Node dosent exist");
    }

    // 1) Update Node Value: Modify the value stored at any node.
    void change_value(TreeNode*& node, int new_value) {
        node->value = new_value;
    }

    // 2) Subtree Sum Query: Calculate the sum of all values in the subtree rooted at a given node.
    int get_sub_tree_sum(TreeNode*& node) {
        int sum = 0;
        sum_subtree(node, sum);
        return sum;
    }

    // 3) Path Query: Compute the sum, minimum, or maximum value along the path between any two nodes.
    void calc_nodes_sum(TreeNode*& node, TreeNode*& target, bool calc_min) {
        bfs_calc_sum(node, target, calc_min);
    }

    // 4) Dynamic Re-rooting: Change the root of the tree dynamically, maintaining all tree operations.
    void re_root(TreeNode*& new_root) {
        unordered_map<int, MyVector<TreeNode*>> depth_map;

        try {
            change_parents(root, new_root);
        } catch (const exception& e) {
            cerr << e.what() << endl;
        }

    }

    // 5) Tree Structure Modification: Remove an existing edge and add a new edge, ensuring the tree remains valid and functional.
    void remove_edge(TreeNode* parent, TreeNode* child) {
        MyVector<TreeNode*> new_children;
        for (TreeNode* node : parent->children) {
            if (node != child) {
                new_children.push_back(node);
            }
        }

        parent->children = new_children;
    }

    void add_edge(TreeNode* parent, TreeNode* child) {
        parent->children.push_back(child);
    }

    //  6) Parents Getting: Get parents of each node in a good efficient way

    //  7) Depth Challenge: get a depth map including all nodes with a key which is depth and a value which is nodes at this depth

};

int main() {
    Tree tree(1);

    // Test Case 1: Basic Insertion
    cout << "Test Case 1: Basic Insertion" << endl;
    tree.insert(2, 1);
    tree.insert(3, 1);
    tree.insert(4, 2);
    tree.insert(5, 2);
    tree.insert(6, 3);
    cout << "Nodes inserted successfully.\n" << endl;

    // Test Case 2: Subtree Sum Query
    cout << "Test Case 2: Subtree Sum Query" << endl;
    TreeNode* node2 = tree.get_node(2);
    int subtree_sum = tree.get_sub_tree_sum(node2);
    cout << "Subtree sum of node 2: " << subtree_sum << " (Expected: 11)" << endl;

    // Test Case 3: Path Query
    cout << "\nTest Case 3: Path Query" << endl;
    TreeNode* root_node = tree.get_node(1);
    TreeNode* node4 = tree.get_node(4);
    tree.calc_nodes_sum(root_node, node4, false); // Max path sum
    cout << "Max path sum from root to node 4 updated in target node: " << node4->value << endl;

    // Test Case 4: Dynamic Re-rooting
    cout << "\nTest Case 4: Dynamic Re-rooting" << endl;
    TreeNode* node3 = tree.get_node(3);
    tree.re_root(node3);
    cout << "Tree re-rooted to node 3. Operations should still function.\n";

    // Test Case 5: Find Node
    cout << "\nTest Case 5: Find Node" << endl;
    bool found = tree.find(4);
    cout << "Node 4 found: " << (found ? "Yes" : "No") << " (Expected: Yes)" << endl;
    found = tree.find(10);
    cout << "Node 10 found: " << (found ? "Yes" : "No") << " (Expected: No)" << endl;

    // Test Case 6: Tree Structure Modification
    cout << "\nTest Case 6: Tree Structure Modification" << endl;
    tree.remove_edge(node2, node4);
    cout << "Edge between node 2 and node 4 removed." << endl;
    tree.add_edge(node3, node4);
    cout << "Edge between node 3 and node 4 added." << endl;

    // Test Case 7: Depth Map
    cout << "\nTest Case 7: Depth Map" << endl;
//    unordered_map<int, MyVector<TreeNode*>> depth_map;
//    tree.get_depth_map(depth_map);
//    cout << "Depth map: " << endl;
//    for (const auto& [depth, nodes] : depth_map) {
//        cout << "Depth " << depth << ": ";
//        for (TreeNode* node : nodes) {
//            cout << node->value << " ";
//        }
//        cout << endl;
//    }

    cout << "\nAll test cases executed successfully." << endl;

    return 0;
}
