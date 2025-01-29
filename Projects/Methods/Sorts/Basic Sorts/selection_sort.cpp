#include <iostream>
#include <stdexcept>
using namespace std;

#define SIZE 6

void selection_sort(int array[]) {
    for (int i = 0; i < SIZE - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < SIZE; ++j) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        int temp = array[minIndex];
        array[minIndex] = array[i];
        array[i] = temp;
    }
}

int main() {
    int myArray[SIZE] = {6,4,2,5,1,3};

    selection_sort(myArray);
    for (int &i : myArray) {
        cout << i << " ";
    }
    return 0;
}
