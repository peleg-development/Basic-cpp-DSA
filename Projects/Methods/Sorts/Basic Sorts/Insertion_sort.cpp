#include <iostream>
#include <stdexcept>
using namespace std;

#define SIZE 6

void insertion_sort(int array[]) {
    for (int i = 1; i < SIZE; ++i) {
        // we use size since size is 0 1 2 3 4 5 ( size = 6 ) and we want to loop on everything from i = 1
        // since we want every element from 1
        for (int j = i; j > 0; --j) {
            // we use j = i since we want to start at i pos lets say i is 1 so j is also 1 now we want to dec until index 0
            if (array[j - 1] > array[j]) {
                // we check if the element before is bigger then current if yes we swap
                int temp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = temp;
            }
        }
    }
}

int main() {
    int myArray[SIZE] = {6,4,2,5,1,3};

    insertion_sort(myArray);
    for (int &i : myArray) {
        cout << i << " ";
    }

    return 0;
}
