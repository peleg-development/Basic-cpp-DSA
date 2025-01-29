#include <iostream>
#include <stdexcept>

using namespace std;

/*
About Hash Table Tables:

A Hash Table Table is a data structure that provides a way to store and retrieve elements using a
key-value mapping with average O(1) time complexity for insertion, deletion, and lookup.

Key Concepts:
1. Hash Table Function:
   - A function that takes a key (e.g., an integer, string) and returns an integer "hash code."
   - This hash code is used to determine which "bucket" the element belongs to.
   - A good hash function evenly distributes keys across buckets to minimize collisions.

2. Buckets:
   - The hash table is divided into several buckets (like containers).
   - Each bucket holds zero or more elements.
   - The hash code of the key determines which bucket an element is placed in.
   - Example: bucket_index = hash(key) % number_of_buckets

3. Collisions:
   - Occur when different keys produce the same bucket index.
   - Common ways to handle collisions:
     - Chaining: Store collided elements in a linked list or another container within the bucket.
     - Open Addressing: Find another bucket using a probe sequence if the initial bucket is full.

4. Average O(1) Complexity:
   - Under good hashing and reasonable load factor, most operations only require looking at
     one or a small number of elements in a bucket.
   - Insert, find, and erase can often be done without traversing large portions of the table.
   - Worst-case operations can degrade to O(n) if many keys end up in the same bucket.

5. Load Factor and Rehashing:
   - Load factor = (number_of_elements) / (number_of_buckets).
   - If the load factor becomes too high, the hash table can resize (rehash) to reduce collisions
     and maintain O(1) average performance.

In summary:
A Hash Table Table uses a hash function to assign keys to buckets, minimizing collisions to achieve
efficient average-time operations. This makes it ideal when fast lookups are critical and
the order of keys does not matter.
*/

/*
If you were to create your own Hash Table Table from scratch, you would need the following key functions:

1) insert(key, value)
   - Inserts a new key-value pair into the hash table if the key does not already exist.
   - If it exists, you may choose to update the value or ignore the insertion.

2) find(key)
   - Searches the hash table for an element with the given key.
   - Returns a handle (iterator, pointer, or special structure) to the element if found, or an indication that it’s not found.

3) erase(key)
   - Removes the element with the specified key from the hash table if it exists.
   - Must handle reordering or linking of elements to maintain the table’s integrity when a bucket loses an element.

4) operator[](key) (Optional)
   - Returns a reference to the value associated with the key.
   - If the key does not exist, you may choose to insert a default-constructed value.

5) at(key) (Optional)
   - Returns a reference to the value associated with the key, or throws an exception (or signals an error) if the key isn’t found.

6) begin() and end() (Optional)
   - Provide iterators or a way to traverse all elements in the hash table.
   - Order is not guaranteed or meaningful in a hash table, but iteration over all elements can be useful.

7) rehash(new_bucket_count) (Optional)
   - Adjusts the number of buckets in the hash table.
   - Called internally when insertions increase the load factor beyond a desired threshold.
   - Helps maintain O(1) average complexity by redistributing elements among buckets.

8) size() and empty()
   - size(): Returns the number of elements currently stored.
   - empty(): Returns true if no elements are in the hash table, false otherwise.

Additionally:
- A hash function (often provided or chosen when creating the hash table) to convert keys to indices.
- A way to handle collisions (chaining or open addressing).
- Functions to maintain and adjust the load factor if implementing automatic rehashing.

By implementing these functions, you can build a functioning hash table data structure from scratch.
*/


class Hash_Table {

};

void hash_table_test() {

}