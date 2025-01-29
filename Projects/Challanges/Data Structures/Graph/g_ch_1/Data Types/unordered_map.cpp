#include <iostream>
#include <stdexcept>

using namespace std;
/*
Challenge 2: std::unordered_map

What is std::unordered_map?
- An associative container that stores key-value pairs but does NOT maintain any order of keys.
- Uses a hash table internally to provide average O(1) time complexity for insert, find, and erase operations.

Built with:
- A Hash Table Table, where elements are placed into "buckets" based on their hashed key.
- If hash collisions occur (different keys with the same hash), elements are linked in the same bucket.

Common operations:
- insert(key, value): Add a new element. Average O(1)
- find(key): Find the value associated with a key. Average O(1)
- operator[](key): Access or insert an element with a given key. Average O(1)
- at(key): Access with bounds checking. Average O(1)
- erase(key): Remove element by key. Average O(1)

This challenge will help you see how a hash-based container can provide very fast lookups
but cannot guarantee order.
*/


class Unordered_Map {

};


void un_map_test() {

}