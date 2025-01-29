#include <iostream>
using namespace std;

#define SIZE 6

// ==========================
// Bubble Sort
// ==========================
/*
Bubble sort works by repeatedly swapping adjacent elements if they are in the wrong order.
With each pass, the largest unsorted element "bubbles up" to its correct position.

- **Best Case (Already Sorted):** O(n) with optimization.
- **Worst Case (Reverse Sorted):** O(n^2).
- **Space Complexity:** O(1) (in-place sorting).
- **Stable:** Yes (does not reorder equal elements).
- **Use Case:** Rarely used due to inefficiency but good for educational purposes.
*/
void bubble_sort(int array[]) {
    for (int i = 0; i < SIZE - 1; ++i) { // Pass through the array
        bool swapped = false; // Track if a swap occurs

        for (int j = 0; j < SIZE - i - 1; ++j) { // Compare adjacent elements
            if (array[j] > array[j + 1]) { // If out of order, swap
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break; // Early exit if no swaps occur
    }
}

// ==========================
// Selection Sort
// ==========================
/*
Selection sort divides the array into sorted and unsorted parts.
For each iteration, it selects the smallest element in the unsorted part and swaps it with the first unsorted element.

- **Best/Worst Case:** O(n^2) (always scans the remaining unsorted part).
- **Space Complexity:** O(1) (in-place sorting).
- **Stable:** No (may reorder equal elements).
- **Use Case:** Simple and intuitive but inefficient for large arrays.
*/
void selection_sort(int array[]) {
    for (int i = 0; i < SIZE - 1; ++i) { // Iterate over the array
        int minIndex = i; // Assume the current index is the smallest

        for (int j = i + 1; j < SIZE; ++j) { // Find the smallest element in the unsorted part
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the smallest element with the first unsorted element
        int temp = array[minIndex];
        array[minIndex] = array[i];
        array[i] = temp;
    }
}

// ==========================
// Insertion Sort
// ==========================
/*
Insertion sort builds the sorted array one element at a time by inserting each new element into its correct position.

- **Best Case (Already Sorted):** O(n).
- **Worst Case (Reverse Sorted):** O(n^2).
- **Space Complexity:** O(1) (in-place sorting).
- **Stable:** Yes (does not reorder equal elements).
- **Use Case:** Efficient for small or nearly sorted arrays.
*/
void insertion_sort(int array[]) { // different way to do insertion sort this is with switching approach
    for (int i = 1; i < SIZE; ++i) { // Start from the second element
        int key = array[i]; // Element to be inserted into the sorted part
        int j = i - 1;

        // Move elements greater than key to one position ahead
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            --j;
        }

        array[j + 1] = key; // Insert the key in its correct position
    }
}

// ==========================
// Utility Function
// ==========================
void print_array(const int array[]) {
    for (int i = 0; i < SIZE; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// ==========================
// Main Function
// ==========================
int main() {
    int bubbleArray[SIZE] = {6, 4, 2, 5, 1, 3};
    int selectionArray[SIZE] = {6, 4, 2, 5, 1, 3};
    int insertionArray[SIZE] = {6, 4, 2, 5, 1, 3};

    cout << "Original Array: \n";
    print_array(bubbleArray);

    // Apply Bubble Sort
    bubble_sort(bubbleArray);
    cout << "Bubble Sort: \n";
    print_array(bubbleArray);

    // Apply Selection Sort
    selection_sort(selectionArray);
    cout << "Selection Sort: \n";
    print_array(selectionArray);

    // Apply Insertion Sort
    insertion_sort(insertionArray);
    cout << "Insertion Sort: \n";
    print_array(insertionArray);

    return 0;
}
