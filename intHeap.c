/**
 *  The functions in this module implement a Heap data structure
 *  of integers.
 */

#include "intHeap.h" // Include the header file for the heap functions
#include <stdio.h>   // Include standard input/output functions (e.g., fprintf)
#include <stdlib.h>  // Include standard library functions (e.g., exit)

int heap[100];      // Array to represent the heap (max size = 100)
static int size = 0; // Current size of the heap (initialized to 0)

/**
 * heapDelete() removes the biggest integer in the heap and returns it.
 */
int heapDelete() {
    if (size == 0) { // Check if the heap is empty
        fprintf(stderr, "Error: Heap is empty.\n"); // Print an error message
        return -1; // Return -1 to indicate an error
    }

    int max = heap[0]; // The maximum element is always at the root (index 0)
    heap[0] = heap[--size]; // Replace the root with the last element in the heap

    // Heapify down: Restore the heap property
    int i = 0; // Start at the root
    while (1) {
        int left = 2 * i + 1;  // Index of the left child
        int right = 2 * i + 2; // Index of the right child
        int largest = i;       // Assume the current node is the largest

        // Check if the left child is larger than the current node
        if (left < size && heap[left] > heap[largest]) largest = left;

        // Check if the right child is larger than the current node
        if (right < size && heap[right] > heap[largest]) largest = right;

        // If the current node is the largest, the heap property is restored
        if (largest == i) break;

        // Swap the current node with the larger child
        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        // Move down to the larger child
        i = largest;
    }

    return max; // Return the maximum element
}

/**
 * addHeap(thing2add) adds the "thing2add" to the Heap.
 */
void addHeap(int thing2add) {
    if (size >= 100) { // Check if the heap is full
        fprintf(stderr, "Error: Heap is full.\n"); // Print an error message
        return; // Exit the function without adding the element
    }

    heap[size++] = thing2add; // Add the new element to the end of the heap

    // Heapify up: Restore the heap property
    int i = size - 1; // Start at the newly added element
    while (i > 0 && heap[(i - 1) / 2] < heap[i]) { // While the parent is smaller
        int temp = heap[(i - 1) / 2]; // Swap the current node with its parent
        heap[(i - 1) / 2] = heap[i];
        heap[i] = temp;

        i = (i - 1) / 2; // Move up to the parent
    }
}

/**
 * heapSize() returns the number of items in the Heap.
 */
int heapSize() {
    return size; // Return the current size of the heap
}