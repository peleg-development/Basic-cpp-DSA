#include <iostream>
#include <vector>
#include <optional>     // For std::optional
#include <utility>      // For std::pair
#include <functional>   // For std::hash
#include <stdexcept>    // For exceptions
// TODO: learn open addressing implementation

/**
 * @brief HashTable class using Open Addressing with Linear Probing.
 *
 * This class provides a generic Hash Table Table implementation that stores key-value pairs.
 * It uses open addressing with linear probing for collision resolution.
 *
 * @tparam K Type of keys.
 * @tparam V Type of values.
 * @tparam Hash Hash Table function type. Defaults to std::hash<K>.
 */
template <typename K, typename V, typename Hash = std::hash<K>>
class HashTable {
private:
    /**
     * @brief Enum to represent the state of each slot in the hash table.
     */
    enum class SlotState { EMPTY, OCCUPIED, DELETED };

    /**
     * @brief Struct to represent each slot in the hash table.
     */
    struct Slot {
        std::optional<std::pair<K, V>> data; // Holds the key-value pair if occupied
        SlotState state;                     // Current state of the slot

        // Constructor
        Slot() : data(std::nullopt), state(SlotState::EMPTY) {}
    };

    std::vector<Slot> table;    // Dynamic array to store slots
    size_t numElements;         // Number of elements currently in the table
    size_t capacity;            // Current capacity of the table (number of slots)
    double maxLoadFactor;       // Maximum allowed load factor before resizing
    Hash hashFunc;              // Hash Table function object

    /**
     * @brief Computes the hash index for a given key.
     *
     * @param key The key to hash.
     * @return size_t The computed index within the table.
     */
    size_t hashFunction(const K& key) const;

    /**
     * @brief Resizes the hash table when the load factor exceeds the threshold.
     * Doubles the capacity and rehashes all existing key-value pairs.
     */
    void resize();

public:
    /**
     * @brief Constructs an empty Hash Table Table with an initial capacity.
     *
     * @param initialCapacity The initial number of slots. Default is 16.
     * @param loadFactorThreshold The load factor threshold to trigger resizing. Default is 0.7.
     */
    HashTable(size_t initialCapacity = 16, double loadFactorThreshold = 0.7);

    /**
     * @brief Destructor to clean up resources.
     */
    ~HashTable();

    /**
     * @brief Inserts a key-value pair into the Hash Table Table.
     * If the key already exists, its value is updated.
     *
     * @param key The key to insert.
     * @param value The value associated with the key.
     */
    void insert(const K& key, const V& value);

    /**
     * @brief Removes a key from the Hash Table Table.
     *
     * @param key The key to remove.
     * @return true If the key was found and removed.
     * @return false If the key was not found.
     */
    bool remove(const K& key);

    /**
     * @brief Searches for a key in the Hash Table Table.
     *
     * @param key The key to search for.
     * @return V* Pointer to the value if found, nullptr otherwise.
     */
    V* search(const K& key);

    /**
     * @brief Checks if the Hash Table Table contains a specific key.
     *
     * @param key The key to check.
     * @return true If the key is present.
     * @return false Otherwise.
     */
    bool containsKey(const K& key) const;

    /**
     * @brief Returns the current number of elements in the Hash Table Table.
     *
     * @return size_t The number of key-value pairs stored.
     */
    size_t getSize() const;

    /**
     * @brief Prints all key-value pairs in the Hash Table Table.
     * Iterates through each slot and prints its contents.
     */
    void printTable() const;

    /**
     * @brief Retrieves all keys stored in the Hash Table Table.
     *
     * @return std::vector<K> A vector containing all keys.
     */
    std::vector<K> keys() const;

    /**
     * @brief Clears all elements from the Hash Table Table, making it empty.
     */
    void clear();

    /**
     * @brief Calculates the current load factor of the Hash Table Table.
     *
     * @return float The load factor (number of elements divided by capacity).
     */
    float loadFactor() const;
};

int main() {
    // Create a hash table with string keys and integer values
    HashTable<std::string, int> hashTable;

    // Test insertion
    hashTable.insert("apple", 100);
    hashTable.insert("banana", 200);
    hashTable.insert("grape", 300);
    hashTable.insert("orange", 400);
    hashTable.insert("melon", 500);

    std::cout << "Hash Table Table after insertions:" << std::endl;
    hashTable.printTable();

    // Test search
    std::string searchKey = "banana";
    int* value = hashTable.search(searchKey);
    if (value) {
        std::cout << "\nFound key " << searchKey << " with value: " << *value << std::endl;
    } else {
        std::cout << "\nKey " << searchKey << " not found." << std::endl;
    }

    // Test removal
    std::string removeKey = "grape";
    bool removed = hashTable.remove(removeKey);
    std::cout << "\nRemoving '" << removeKey << "': " << (removed ? "Successful" : "Not found") << std::endl;

    std::cout << "\nHash Table Table after deletion:" << std::endl;
    hashTable.printTable();

    // Retrieve all keys
    std::vector<std::string> allKeys = hashTable.keys();
    std::cout << "\nAll keys in the hash table:" << std::endl;
    for (const std::string& key : allKeys) {
        std::cout << key << std::endl;
    }

    // Test containsKey
    std::cout << "\nContains 'apple': " << (hashTable.containsKey("apple") ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'grape': " << (hashTable.containsKey("grape") ? "Yes" : "No") << std::endl;

    // Test size and load factor
    std::cout << "\nCurrent size of hash table: " << hashTable.getSize() << std::endl;
    std::cout << "Current load factor: " << hashTable.loadFactor() << std::endl;

    // Test clear
    hashTable.clear();
    std::cout << "\nHash Table table after clearing:" << std::endl;
    hashTable.printTable();
    std::cout << "Current size of hash table: " << hashTable.getSize() << std::endl;

    return 0;
}
