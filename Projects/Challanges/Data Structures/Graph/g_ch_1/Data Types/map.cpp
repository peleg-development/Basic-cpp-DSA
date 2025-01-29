#include <iostream>
#include <stdexcept>

using namespace std;

/*
std::map explanation with Red-Black Tree details:

std::map is typically implemented using a Red-Black Tree, a type of self-balancing binary search tree.
This is not mandated by the standard, but is the common approach.

Red-Black Tree Characteristics:
- Each node is colored either red or black.
- The root is always black.
- Red nodes never have red children (no two reds in a row).
- Every path from the root to a leaf (or a null child) has the same number of black nodes.

These rules ensure that the tree stays approximately balanced, keeping its height O(log n).
As a result, operations such as insert, find, and erase run in O(log n) time.

Key std::map Operations:
- insert(key, value): Insert a new key-value pair. O(log n)
- find(key): Search for a key. O(log n)
- erase(key): Remove a key-value pair. O(log n)
- operator[](key): Access or create an element by key. O(log n)
- at(key): Access element by key with bounds checking. O(log n)
- Iteration: When you iterate over a std::map, you get keys in ascending order due to the underlying sorted tree structure.

In summary:
std::map uses a balanced tree (often a Red-Black Tree) to maintain sorted keys and provide O(log n) complexity for fundamental operations.
*/


class Map {

};


void map_test() {

}