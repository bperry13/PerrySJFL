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


////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

struct Data {
    int i;
    struct Data *next;
};


////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES
int ticks, process_count, current_process, t;
float tau;


////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS


////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS

void addProcess(struct Data** front, int i) {

    //allocate mem for new node
    struct Data* new_node = malloc(sizeof(struct Data));
    struct Data* last = *front;

    //add data to new node
    new_node->i = i;

    //make next of new node NULL
    new_node->next = NULL;

    //if Linked List is empty set new node to front
    if (*front == NULL) {
        *front = new_node;
        return;
    }

    //else traverse until last node
    else {
        while (last->next != NULL)
            last = last->next;
    }

    //change the next of last node
    last->next = new_node;
}

void display(struct Data *node) {
    //printf("Ticks: %d\n", ticks);
    //printf("Process Count: %d\n", process_count);
    while (node != NULL) {
        printf("Node Data: %d\n", node->i);
        node = node->next;
    }
    printf("\n\n");
}

void destroy(struct Data *node) {
    if (node != NULL) {
        while (node->next != NULL) {
            free(node);
            node = node->next;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
//MAIN METHOD

int main(int argc, char* argv[]) {

    FILE* fp;
    char line[sizeof(long int)];
    char *input_file = argv[optind];
    double x;
    char *ptr;
    struct Data* head = NULL;

    fp = fopen(input_file, "r");

    //check if file loaded properly
    if (fp == NULL) {
        printf("No file to load\n");
        return EXIT_FAILURE;
    }

    printf("==Shortest-Job-First==\n");

    // reads each line and adds to the
    int i = 0, y = 0;
    /**
    while (fgets(line, sizeof(line), fp)) {
        x = strtol(line, &ptr, 10);
        //f = strtod(line, &ptr);

        addProcess(&head, x);
        i++;
    }
     */

    fscanf(fp, "%d", &ticks);
    printf("ticks: %d\n", ticks);
    fscanf(fp, "%d", &process_count);
    printf("process count: %d\n", process_count);
    fscanf(fp, "%d", &current_process);
    printf("current process: %d\n", current_process);
    fscanf(fp, "%d", &t);
    printf("t value: %d\n", t);
    fscanf(fp, "%f", &tau);
    printf("tau value: %f\n", tau);
    while (i < ticks) {
        fscanf(fp, "%d", &y);
        printf("tick: %d value: %d\n", i, y);
        i++;
    }

    while (current_process < process_count) {

        fscanf(fp, "%d", &current_process);
        printf("current process: %d\n", current_process);
        fscanf(fp, "%d", &t);
        printf("t value: %d\n", t);
        fscanf(fp, "%f", &tau);
        printf("tau value: %f\n", tau);
        i = 0;
        while (i < ticks) {
            fscanf(fp, "%d", &y);
            printf("tick: %d value: %d\n", i, y);
            i++;
        }
    }


    fclose(fp);
    return EXIT_SUCCESS;
}

