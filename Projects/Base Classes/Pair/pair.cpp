#include <iostream>
#include <stdexcept>

using namespace std;

/*
Challenge 4: std::pair

What is std::pair?
- A simple template class that groups two values (first and second) into a single unit.
- Often used to store key-value pairs before inserting into maps or to return multiple values from a function.

Built with:
- Essentially just a small struct holding two public members: first and second.
- No complicated internal structure.

Common operations:
- pair<T1, T2> p(x, y): Create a pair from x and y.
- p.first, p.second: Access the stored values.
- make_pair(x, y): A utility function to create pairs easily.
- Comparisons: Lexicographical comparison by first element, then by second.

By completing this challenge, you will learn how to conveniently group two related values,
making your code cleaner and avoiding the need for custom structs for simple tasks.
*/


class Pair {
private:
    int x;
    int y;
public:
    Pair(int x, int y) {
        this->x = x;
        this->y = y;
    }
    ~Pair() = default;

    int first() {
        return this->x;
    }

    int second() {
        return this->y;
    }

};

void pair_test() {

}