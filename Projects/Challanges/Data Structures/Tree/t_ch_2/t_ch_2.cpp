#include <iostream>
#include <stdexcept>
#include <unordered_map>

using namespace std;

/*
Pinned Tree Challenge:

You are given a tree of N nodes, numbered 1 through N. A tree is an acyclic connected
graph with exactly N-1 edges. Your tasks are:

1) Tree Construction:
   - Read N and the N-1 edges.
   - Construct the tree using adjacency lists (e.g., a vector<vector<int>> or
     a map<int, vector<int>> if nodes are not 1-indexed).
   - Ensure that you store the tree efficiently. Since this is a tree, you do not need
     to worry about direction; it’s inherently undirected.

2) Depth-First Search (DFS) and Tree Properties:
   - Implement DFS from a root node (e.g., node 1) to:
     a) Compute the height of the tree (the longest path from the root to a leaf).
     b) Count the number of nodes in each subtree.
   - Store results in arrays/vectors, for example:
     - `height[node]` = height of the subtree rooted at `node`.
     - `subtree_size[node]` = number of nodes in the subtree rooted at `node`.

3) Diameter of the Tree:
   - The diameter of a tree is the length of the longest path between any two nodes.
   - Implement a method to find the diameter using two DFS passes:
     - First, run DFS from an arbitrary node to find the farthest node A.
     - Second, run DFS from A to find the farthest node B. The distance from A to B is the diameter.
   - Output the diameter of the tree.

4) Optional (Advanced) - Lowest Common Ancestor (LCA):
   - Preprocess the tree using a binary lifting technique or a parent-depth array.
   - Implement a function `LCA(u, v)` that finds the lowest common ancestor of two nodes u and v.
   - This is optional but will deepen your understanding of tree queries.

Data Structures to Use:
- `std::vector<std::vector<int>>` for adjacency lists.
- `std::vector<int>` for height, subtree_size, and parent arrays.
- `std::pair<int,int>` could be useful to store intermediate DFS results like (farthest_node, distance).
- If you implement LCA with binary lifting, use a `std::vector<std::vector<int>>` for ancestor jumps.

Complexity Considerations:
- Building the tree: O(N)
- DFS: O(N)
- Diameter calculation (two DFS passes): O(N)
- LCA preprocessing (if implemented): O(N log N)
- LCA queries: O(log N) per query.

Below is a conceptual code outline (not fully fleshed out, but shows how you might structure it):

----------------------------------------------------------
Code Explanation (Conceptual Outline):
----------------------------------------------------------

// Steps:
// 1) Read N and edges
// 2) Build adjacency list
// 3) Implement DFS to get subtree sizes and heights
// 4) Use DFS to find diameter
// 5) (Optional) Preprocess LCA and implement LCA queries

#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> adj; // adjacency list
vector<int> height, subtree_size, parent;

// Simple DFS to compute subtree sizes and heights from a root
void dfs_basic(int node, int par, int depth) {
    parent[node] = par;
    height[node] = depth;
    subtree_size[node] = 1; // count itself
    for (int nxt : adj[node]) {
        if (nxt == par) continue; // avoid going back to parent
        dfs_basic(nxt, node, depth + 1);
        subtree_size[node] += subtree_size[nxt];
    }
}

// DFS to find the farthest node and distance starting from 'start'
pair<int,int> dfs_farthest(int node, int par, int dist) {
    pair<int,int> best = {dist, node};
    for (int nxt : adj[node]) {
        if (nxt == par) continue;
        pair<int,int> candidate = dfs_farthest(nxt, node, dist + 1);
        if (candidate.first > best.first) best = candidate;
    }
    return best;
}

// Compute diameter using two DFS passes
int find_diameter() {
    // First DFS from node 1 (arbitrary)
    pair<int,int> farA = dfs_farthest(1, -1, 0);
    // farA.second is the farthest node from node 1
    // Second DFS from farA.second
    pair<int,int> farB = dfs_farthest(farA.second, -1, 0);
    // The distance farB.first is the diameter
    return farB.first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    adj.assign(N+1, {}); // assuming 1-indexed
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    height.assign(N+1, 0);
    subtree_size.assign(N+1, 0);
    parent.assign(N+1, -1);

    // Run initial DFS from node 1 (can choose any node as root in a tree)
    dfs_basic(1, -1, 0);

    // Find and print the diameter of the tree
    cout << "Diameter of the tree: " << find_diameter() << "\n";

    return 0;
}

/*
By completing this challenge, you will:
- Understand how to represent a tree in code.
- Use DFS to compute basic properties like subtree size and height.
- Learn a technique to find the tree diameter.
- (Optionally) delve into more complex tree queries like LCA, enhancing your understanding
  of tree algorithms and data structures.
*/


int main() {


    return 0;
}