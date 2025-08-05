#include <stdio.h>   
#include <stdlib.h>  
#include <ctype.h>   
#include <string.h>  

// Declare external functions (defined in stringStack.c)
extern char *pop();      // Function to pop a tag from the stack
extern void push(char *); // Function to push a tag onto the stack
extern int isEmpty();     // Function to check if the stack is empty

int main(int argc, char *argv[]) {
    int ch;              // Variable to store the current character from input
    char tag[100];       // Buffer to store the tag name (e.g., "a", "b")
    int tagIndex = 0;    // Index to track the position in the tag buffer
    int isTag = 0;       // Flag to indicate if we're inside a tag (1 = inside, 0 = outside)
    int isEmptyInput = 1; // Flag to check if the input is empty (1 = empty, 0 = not empty)

    printf("Starting XML validation...\n"); // Print a message to indicate the program has started

    // Read input character by character until the end of input (EOF)
    while ((ch = getchar()) != EOF) {
        isEmptyInput = 0; // Set the flag to indicate input is not empty

        // Skip characters that are not part of a tag (e.g., spaces, newlines)
        if (!(isalpha(ch) || ch == '>' || ch == '<' || ch == '/'))
            continue;

        // If the character is '<', it's the start of a tag
        if (ch == '<') {
            isTag = 1;    // Set the flag to indicate we're inside a tag
            tagIndex = 0; // Reset the tag buffer index
        }
        // If the character is '>', it's the end of a tag
        else if (ch == '>') {
            if (isTag) {  // If we're inside a tag
                tag[tagIndex] = '\0'; // Null-terminate the tag name (end the string)

                // If the tag is an end-tag (e.g., </a>)
                if (tag[0] == '/') {
                    // Pop the last start-tag from the stack
                    char *startTag = pop();

                    // Check if the popped start-tag matches the end-tag
                    if (startTag == NULL || strcmp(startTag, tag + 1) != 0) {
                        // If they don't match, print an error and exit
                        fprintf(stderr, "Invalid XML: Mismatched tags.\n");
                        exit(1);
                    }
                }
                // If the tag is a start-tag (e.g., <a>)
                else {
                    // Push the tag onto the stack
                    push(strdup(tag)); // strdup creates a copy of the tag
                }
            }
            isTag = 0; // Reset the flag to indicate we're outside a tag
        }
        // If we're inside a tag, store the character in the tag buffer
        else if (isTag) {
            tag[tagIndex++] = ch;
        }
    }

    // Print a message to indicate the program has finished reading input
    printf("Finished reading input. isEmptyInput = %d\n", isEmptyInput);

    // Handle empty input
    if (isEmptyInput) {
        // If the input is empty, print "Valid XML." and exit
        printf("Valid XML.\n");
        exit(0);
    }

    // Check if the stack is empty
    if (!isEmpty()) {
        // If the stack is not empty, print an error and exit
        fprintf(stderr, "Invalid XML: Unmatched start-tags.\n");
        exit(1);
    }

    // If the stack is empty, print "Valid XML." and exit
    printf("Valid XML.\n");
    exit(0);
}