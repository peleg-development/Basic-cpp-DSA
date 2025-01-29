#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

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
    vector<list<Bucket>> table;

    // Current size of the hash table
    size_t tableSize;

    // Hash Table function
    function<size_t(const K&)> hashFunc;

public:
    /**
     * @brief Construct a new HashTable with a given size and hash function.
     * @param size Initial size of the table.
     * @param hashFunction Custom hash function.
     */
    HashTable(size_t size, function<size_t(const K&)> hashFunction)
            : table(size), tableSize(size), hashFunc(hashFunction) {}


    /**
     * @brief Destructor for the HashTable class.
     */
    ~HashTable() = default;

    /**
     * @brief Insert a key-value pair into the hash table.
     * @param key The key to insert.
     * @param value The value associated with the key.
     */
    void insert(const K& key, const V& value) {
        size_t hash = hashFunc(key);
        Bucket new_bucket = Bucket(key, value);
        table[hash].emplace_back(new_bucket);
    }

    /**
     * @brief Remove a key from the hash table.
     * @param key The key to remove.
     */
    void remove(const K& key) {
        size_t hash = hashFunc(key) % tableSize;
        auto& bucketList = table[hash];
        for (auto it = bucketList.begin(); it != bucketList.end(); ++it) {
            if (it->key == key) {
                bucketList.erase(it);
                return;
            }
        }
        throw runtime_error("Key not found");
    }

/**
 * @brief Find the value associated with a key.
 * @param key The key to search for.
 * @return The value associated with the key.
 */
    V find(const K& key) const {
        size_t hash = hashFunc(key) % tableSize;
        const auto& bucketList = table[hash];
        for (const auto& bucket : bucketList) {
            if (bucket.key == key) {
                return bucket.value;
            }
        }
        throw runtime_error("Key not found");
    }

/**
 * @brief Clear the hash table, removing all entries.
 */
    void clear() {
        for (auto& bucketList : table) {
            bucketList.clear();
        }
    }
};

int main() {
    // Base class demonstration
    // Functions should be implemented to make this functional.

    cout << "HashTable base class created. Functions are not implemented yet." << endl;

    // Test case: Create a HashTable with a custom hash function
    HashTable<int, string> hashTable(10, [](const int& key) {
        return key % 10;
    });

    // Test case: Insert key-value pairs
    cout << "Test case: Inserting key-value pairs..." << endl;
    hashTable.insert(1, "One");
    hashTable.insert(11, "Eleven");
    hashTable.insert(21, "Twenty-One");

    // Test case: Find a key
    cout << "Test case: Finding keys..." << endl;
    try {
        cout << "Key 11: " << hashTable.find(11) << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Test case: Remove a key
    cout << "Test case: Removing a key..." << endl;
    hashTable.remove(11);

    // Test case: Clear the hash table
    cout << "Test case: Clearing the hash table..." << endl;
    hashTable.clear();

    return 0;
}
