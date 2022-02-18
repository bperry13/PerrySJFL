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
int ticks = 0, process_count = 0, current_process = 0, t = 0;
int tot_turn_time = 0, turn_time = 0, tot_wait_time = 0, wait_time = 0, error_est = 0;
float tau = 0;


////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS


////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS

//Shortest Job First algorithm
void sjf(FILE *fp, int ticks, int process_count) {
    int i = 0, y = 0, t = 0;
    printf("==Shortest-Job-First==\n");
    while (current_process < (process_count - 1)) {

        fscanf(fp, "%d", &current_process);
        fscanf(fp, "%d", &t);
        fscanf(fp, "%f", &tau);
        printf("Simulating %dth tick of processes @ time %d:\n", i, t);

        while (t < ticks) {

            fscanf(fp, "%d", &y);
            t += t;
            printf("Process %d took %d\n", current_process, t);
            //TODO: calculate SJF
            t++;
        }
    }

    printf("Turnaround time: TBD\n"); //TODO: calculate turnaround time
    printf("Waiting time: TBD\n"); //TODO: calculate wait time
}

//Shortest Job First Live algorithm
void sjf_live() {
    printf("==Shortest-Job-First Live==\n");
    printf("Estimation error: %d\n", error_est);
}


////////////////////////////////////////////////////////////////////////////////
//MAIN METHOD

int main(int argc, char* argv[]) {

    FILE* fp;
    //char line[sizeof(long int)];
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



    fscanf(fp, "%d", &ticks);
    printf("total ticks: %d\n", ticks);
    fscanf(fp, "%d", &process_count);
    printf("total process count: %d\n", process_count);

    //run SJF algorithm
    sjf(fp, ticks, process_count);

    //TODO: create sjf live algorithm
    sjf_live();

    fclose(fp);
    return EXIT_SUCCESS;
}

