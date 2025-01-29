#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

/*
 * & = AND
 * | = OR
 * ^ = XOR
 * << left shift
 * >> right shift
 */


int main() {
    int x = 6; // 6 = 00000110
    int y = 12; // 12 = 00001100
    int z = 0; // 0 = 00000000

    z = x & y;
    // 00000110
    // 00001100
  //z  00000100 = 4

    return 0;
}