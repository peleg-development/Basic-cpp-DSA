#include <iostream>
#include <vector>
#include <utility>      // for std::pair
#include <functional>   // for std::hash

/**
 * @brief HashTable class using custom Node-based separate chaining.
 *
 * This class provides a skeleton for a generic Hash Table Table, which stores key-value pairs.
 * It uses separate chaining with custom singly linked lists to handle collisions.
 * The table resizes itself when the load factor exceeds a certain threshold to maintain
 * efficient average-case time complexity for operations.
 *
 * @tparam K Type of keys.
 * @tparam V Type of values.
 */
template <typename K, typename V>
class HashTable {
private:
    // Node structure for separate chaining
    struct Node {
        K key;
        V value;
        Node* next;

        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    // Vector of pointers to the head nodes of the chains
    std::vector<Node*> table;

    // Number of elements stored in the hash table
    size_t numElements;

    // Current capacity of the hash table (number of buckets)
    size_t capacity;

    // Maximum load factor before resizing
    const double maxLoadFactor = 0.75;

    /**
     * @brief Hash Table function to compute the index for a given key.
     * Uses std::hash by default, but can be customized.
     *
     * @param key The key to hash.
     * @return size_t The index corresponding to the key.
     */
    size_t hashFunction(const K& key) const {

    }

    /**
     * @brief Resize the hash table when the load factor exceeds the threshold.
     * Doubles the capacity and rehashes all existing key-value pairs.
     */
    void resize() {

    }

public:
    /**
     * @brief Construct an empty Hash Table Table with an initial capacity.
     *
     * @param initialCapacity The initial number of buckets. Default is 16.
     */
    HashTable(size_t initialCapacity = 16)
            : table(initialCapacity, nullptr), numElements(0), capacity(initialCapacity) {}

    /**
     * @brief Destroy the Hash Table Table, releasing all resources.
     */
    ~HashTable() {

    }

    /**
     * @brief Insert a key-value pair into the Hash Table Table.
     * If the key already exists, its value is updated.
     *
     * @param key The key to insert.
     * @param value The value associated with the key.
     */
    void insert(const K& key, const V& value) {

    }

    /**
     * @brief Remove a key from the Hash Table Table.
     *
     * @param key The key to remove.
     * @return true If the key was found and removed.
     * @return false If the key was not found.
     */
    bool remove(const K& key) {

    }

    /**
     * @brief Search for a key in the Hash Table Table.
     *
     * @param key The key to search for.
     * @return V* Pointer to the value if found, nullptr otherwise.
     */
    V* search(const K& key) const {

    }

    /**
     * @brief Check if the Hash Table Table contains a key.
     *
     * @param key The key to check.
     * @return true If the key is present.
     * @return false Otherwise.
     */
    bool contains(const K& key) const {

    }

    /**
     * @brief Get the current number of elements in the Hash Table Table.
     *
     * @return size_t The number of key-value pairs stored.
     */
    size_t size() const {

    }

    /**
     * @brief Print all key-value pairs in the Hash Table Table.
     * Iterates through each bucket and prints the contents.
     */
    void printAll() const {

    }

    /**
     * @brief Clear all elements from the Hash Table Table, making it empty.
     */
    void clear() {

    }
};
