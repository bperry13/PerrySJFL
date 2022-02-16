/**
 * write a program that simulates using the shortest-jobf irst (SJF)
 * algorithm(s) to pick which processes should be scheduled in what
 * order
 *
 * Completion time: 5 hours
 *
 * @author: Brett Perry
 * @version: 2.14.22
 */

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

////////////////////////////////////////////////////////////////////////////////
//MACROS: CONSTANTS
#define LINE_LEN 72


////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES
struct Node {
    int data;
    struct Node *next;
};


////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES
struct Node* head = NULL;



////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS

void addLast(struct Node** head_ref, int new_data) {
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    struct Node *last = *head_ref;  /* used in step 5*/

    /* 2. put in the data  */
    new_node->data = new_data;

    /* 3. This new node is going to be the last node, so make next
          of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
}

void *display(struct Node *node) {
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
}

int main(int argc, char* argv[]) {

    FILE* fp;
    char line[sizeof(long int)];
    char *input_file = argv[optind];
    double x;
    char *ptr;

    fp = fopen(input_file, "r");

    //check if file loaded properly
    if (fp == NULL) {
        printf("No file to load\n");
        return 1;
    }

    // reads each line
    while (fgets(line, sizeof(line), fp)) {
        x = strtod(line, &ptr);
        printf("%f\n", x);
        //addLast(head, x);
    }

    printf("\n\n\n");

    fclose(fp);
    //display(head);
    //free(head);

    return 0;
}

