#include <iostream>
#include <stdexcept>
using namespace std;

#define SIZE 6

void bubbleSort(int array[]) {
    for (int i = SIZE - 1; i > 0; i--) {
        bool swapped = false;
        for (int j = 0; j < i; j++) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}


int main() {

    int myArray[SIZE] = {6,4,2,5,1,3};

    bubbleSort(myArray);
    for (int &i : myArray) {
        cout << i << " ";
    }


    return 0;
}
