#include <iostream>
#include <stdexcept>
using namespace std;

#define SIZE 11

void create_sub_array(int source[], int start_index, int size, int sub_array[]) {
    for (int i = 0; i < size; i++) {
        sub_array[i] = source[start_index + i];
    }
}

void merge_subarrays(int array[], int& index, int leftArray[], int leftArraySize, int rightArray[], int rightArraySize, int& i, int& j) {
    while (i < leftArraySize && j < rightArraySize) {
        if (leftArray[i] <= rightArray[j]) {
            array[index] = leftArray[i];
            i++;
        }
        else {
            array[index] = rightArray[j];
            j++;
        }
        index++;
    }
}

void handle_remaining_elements(int array[], int& index, int leftArray[], int leftArraySize, int rightArray[], int rightArraySize, int i, int j) {
    while (i < leftArraySize) {
        array[index] = leftArray[i];
        index++;
        i++;
    }

    while (j < rightArraySize) {
        array[index] = rightArray[j];
        index++;
        j++;
    }
}

int* merge(int array[], int leftIndex, int midIndex, int rightIndex) {
    int leftArraySize = midIndex - leftIndex + 1;
    int rightArraySize = rightIndex - midIndex;

    int leftArray[leftArraySize];
    int rightArray[rightArraySize];

    create_sub_array(array, leftIndex, leftArraySize, leftArray);
    create_sub_array(array, midIndex + 1, rightArraySize, rightArray);

    int index = leftIndex;
    int i = 0;
    int j = 0;

    merge_subarrays(array, index, leftArray, leftArraySize, rightArray, rightArraySize, i, j);

    handle_remaining_elements(array, index, leftArray, leftArraySize, rightArray, rightArraySize, i, j);

    return array;
}

void merge_sort(int array[], int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        int midIndex = (leftIndex + rightIndex) / 2;

        merge_sort(array, leftIndex, midIndex);

        merge_sort(array, midIndex + 1, rightIndex);

        merge(array, leftIndex, midIndex, rightIndex);
    }
}

int* merge_sort(int array[]) {
    merge_sort(array, 0, SIZE);
    return array;
}

int main() {
    int myArray[] = {1, 7, 3, 6, 8, 11, 5, 4, 2, 9, 10, 12};

    merge_sort(myArray);

    for (auto value : myArray) {
        cout << value << " ";
    }



    return 0;
}
