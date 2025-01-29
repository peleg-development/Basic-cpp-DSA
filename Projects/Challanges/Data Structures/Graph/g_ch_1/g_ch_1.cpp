#include <iostream>
#include <stdexcept>

using namespace std;

/*
1) Basic Graph Construction:
   - Data Structure: Use a vector or map of vectors (std::map<int, std::vector<std::pair<int,int>>>),
                     where keys are nodes and values are adjacency lists of (neighbor, weight).
   - Adding an edge: O(1) amortized if using a vector, O(log N) if using a map (for N nodes).
   - For M edges, building the entire graph: O(M) if vectors are directly accessible, O(M log N) if maps are used.

2) Shortest Path Queries (Dijkstra’s Algorithm):
   - Using a min-priority queue (typically a binary heap):
     - Each edge relaxation: O(log N) due to priority queue operations.
     - Complexity: O(M log N) where M is the number of edges and N is the number of nodes.
   - Data Structures:
     - dist array: O(N)
     - visited array: O(N)
     - priority queue operations: O(M log N)

3) Topological Sorting & DAG Detection:
   - Topological sort using in-degree array:
     - Compute in-degrees: O(M)
     - Queue operations: O(N)
     - Overall complexity: O(N + M)
   - Data Structures:
     - in-degree array/vector: O(N)
     - queue: O(N)

4) Strongly Connected Components (SCC):
   - Using Tarjan’s Algorithm or Kosaraju’s Algorithm:
     - Tarjan’s: O(N + M) (single DFS-based approach)
     - Kosaraju’s: O(N + M) (two DFS passes: one on the original graph, one on the reversed graph)
   - Data Structures:
     - stack for Tarjan’s: O(N)
     - arrays for discovery times, low-link values: O(N)
     - reversed graph construction for Kosaraju’s: O(N + M)

5) Complex Queries (MST or Max Flow):
   - MST (Kruskal’s):
     - Sorting edges: O(M log M)
     - Union-Find operations: O(M α(N)), where α(N) is the inverse Ackermann function (practically constant).
     - Overall: O(M log M) dominated by sorting.
     - Data Structures:
       - Union-Find: O(N) initialization, near O(1) per union/find.
       - vector of edges: O(M)

   - Max Flow (Edmond-Karp):
     - O(N * M^2) in the worst case (but often faster in practice).
     - If using Dinic’s Algorithm: O(min{N^(2/3), sqrt(M)} * M) or O(M√N) in many special cases.
   - Data Structures:
     - residual graph: O(N + M)
     - queue: O(N) per BFS in Edmond-Karp

By addressing complexity, you’ll understand:
   - How to select appropriate data structures (vectors vs. maps, priority queues, stacks, queues).
   - The scalability of each graph operation and algorithm.
   - Why certain data structures and algorithms are chosen to handle large graphs efficiently.
*/

/*
Limitations / Constraints:

- Node and Edge Counts:
  - Depending on the environment, you may face memory and performance limitations.
  - If N (number of nodes) and M (number of edges) become very large (e.g., millions), even O(M log N) operations could be too slow.
  - Storing large graphs might require careful consideration of memory (e.g., using std::vector instead of std::map where possible).

- Memory Constraints:
  - Using maps for adjacency lists might cause overhead due to tree-based structures internally.
  - Consider using vectors indexed by integer node IDs for more direct O(1) access.
  - Large arrays and vectors need pre-allocation based on known maximum N and M.

- Algorithmic Complexity:
  - Certain algorithms (e.g., Edmond-Karp for max flow) can be too slow (O(N*M^2)) for very large graphs.
  - More efficient algorithms (Dinic’s, Push-Relabel, etc.) may be required for large constraints.

- Data Structure Choice:
  - Union-Find with path compression and union by rank is nearly O(1) per operation, but naive union-find might degrade performance.
  - For shortest paths in sparse graphs, Dijkstra’s with a priority queue is efficient, but for dense graphs, even O(M log N) might be expensive.

- Practical Implementation Details:
  - Using recursion for DFS-based algorithms (Tarjan’s SCC, Kosaraju’s, etc.) may hit recursion depth limits.
  - Iterative approaches or increasing stack size might be necessary for very large graphs.
  - When dealing with maximum flow, careful memory and pointer manipulation in residual graphs is crucial for performance.

In summary, while no strict numerical limits are imposed by the challenge statement itself, practical considerations such as the size of N and M, available memory, and expected execution time will influence the chosen data structures and algorithms. The challenge is to implement robust solutions, but in real scenarios, you must balance complexity, memory usage, and performance.
*/


int main() {


    return 0;
}