#include <stdio.h>   
#include <stdlib.h>  
#include <ctype.h>   
#include "intHeap.h" 
#include "intStack.h" 
// Declare external functions (defined in intHeap.c and intStack.c)
extern int pop();         // Function to pop an element from the stack
extern void push(int);    // Function to push an element onto the stack
extern void addHeap(int); // Function to add an element to the heap
extern int heapDelete();  // Function to delete the maximum element from the heap
extern int heapSize();    // Function to get the current size of the heap

/**
 * Recursively prints the heap as an XML tree.
 */
void printHeapAsXML(int index) {
    if (index >= heapSize()) return; // Stop if the index is out of bounds

    // Print the current node in XML format
    printf("<node id=\"%d\">", heap[index]);

    // Recursively print the left child (2 * index + 1)
    printHeapAsXML(2 * index + 1);

    // Recursively print the right child (2 * index + 2)
    printHeapAsXML(2 * index + 2);

    // Close the current node
    printf("</node>");
}

/**
 * The main function reads integers from stdin, adds them to the heap,
 * prints the heap as an XML tree, and then prints the integers in
 * sorted and reverse-sorted order.
 */
int main(int argc, char *argv[]) {
    int value; // Variable to store the current integer from input

    // Read integers from input until the end of input (EOF)
    while (scanf("%d\n", &value) != EOF) {
        fprintf(stderr, "%d\n", value); // Print Numbers
        addHeap(value); // Add the value to the heap
    }

    // Print the heap as an XML tree
    printf("Heap as XML:\n");
    printHeapAsXML(0); // Start printing from the root (index 0)
    printf("\n");

    // Delete elements from the heap and push them onto the stack
    while (heapSize() > 0) {
        int max = heapDelete(); // Delete the maximum element from the heap
        printf("%d\n", max);    // Print the element (sorted order, descending)
        push(max);              // Push the element onto the stack
    }

    // Pop elements from the stack and print them (reverse-sorted order, ascending)
    printf("Reverse-sorted order:\n");
    while (!isEmpty()) {
        printf("%d\n", pop()); // Pop and print each element
    }

    exit(0); // Exit the program
}
