#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
/**
 * @brief HashTable class
 *
 * This class provides a skeleton for a generic hash table.
 * It uses separate chaining to handle collisions.
 */
template <typename K, typename V>
class HashTable {
protected:
    // A single bucket in the hash table
    struct Bucket {
        K key;
        V value;

        Bucket(K k, V v) : key(k), value(v) {}
    };

    // Vector of lists (buckets) to store key-value pairs
    std::vector<std::list<Bucket>> table;

    // Current size of the hash table
    size_t tableSize;

    // Hash Table function
    std::function<size_t(const K&)> hashFunc;

public:
    /**
     * @brief Construct a new HashTable with a given size and hash function.
     * @param size Initial size of the table.
     * @param hashFunction Custom hash function.
     */
    HashTable(size_t size, std::function<size_t(const K&)> hashFunction);

    /**
     * @brief Destructor for the HashTable class.
     */
    ~HashTable();

    /**
     * @brief Insert a key-value pair into the hash table.
     * @param key The key to insert.
     * @param value The value associated with the key.
     */
    void insert(const K& key, const V& value);

    /**
     * @brief Remove a key from the hash table.
     * @param key The key to remove.
     */
    void remove(const K& key);

    /**
     * @brief Find the value associated with a key.
     * @param key The key to search for.
     * @return The value associated with the key.
     */
    V find(const K& key) const;

    /**
     * @brief Clear the hash table, removing all entries.
     */
    void clear();
};

int main() {
    // Base class demonstration
    // Functions should be implemented to make this functional.

    std::cout << "HashTable base class created. Functions are not implemented yet." << std::endl;

    // Test case: Create a HashTable with a custom hash function
    HashTable<int, std::string> hashTable(10, [](const int& key) {
        return key % 10;
    });

    // Test case: Insert key-value pairs
    std::cout << "Test case: Inserting key-value pairs..." << std::endl;
    hashTable.insert(1, "One");
    hashTable.insert(11, "Eleven");
    hashTable.insert(21, "Twenty-One");

    // Test case: Find a key
    std::cout << "Test case: Finding keys..." << std::endl;
    try {
        std::cout << "Key 11: " << hashTable.find(11) << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // Test case: Remove a key
    std::cout << "Test case: Removing a key..." << std::endl;
    hashTable.remove(11);

    // Test case: Clear the hash table
    std::cout << "Test case: Clearing the hash table..." << std::endl;
    hashTable.clear();

    return 0;
}
