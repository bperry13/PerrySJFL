/**
 * write a program that simulates using the shortest-job first (SJF)
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
struct Process {
    int pid;
    int tau;
    float alpha;
    int *t;
};

////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES

////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS

////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS

void create_procs(FILE *fp, struct Process *p, int tot_procs, int tot_ticks) {
    for (int i = 0; i < tot_procs; i++) {
        fscanf(fp, "%d", &p[i].pid);
        //printf("%d\n", p[i].pid);
        fscanf(fp, "%d", &p[i].tau);
        //printf("%d\n", p[i].tau);
        fscanf(fp, "%f", &p[i].alpha);
        //printf("%f\n", p[i].alpha);
        p[i].t = malloc(sizeof(int) * tot_ticks);
        for (int j = 0; j < tot_ticks; j++) {
            fscanf(fp, "%d", &p[i].t[j]);
            //printf("%d\n", p[i].t[j]);
        }
    }
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubble_sort(int temp_arr[], int tot_procs) {
    int i, j;
    for (i = 0; i < tot_procs - 1; i++)
        for (j = 0; j < tot_procs - i - 1; j++)
            if (temp_arr[j] > temp_arr[j+1])
                swap(&temp_arr[j], &temp_arr[j+1]);
}

void print_sjf(int *temp_arr, int tot_procs) {
    for (int i = 0; i < tot_procs; i++) {
        printf("Process %d took %d\n", i, temp_arr[i]);
    }
}

void print_sjfl(int *temp_arr, int est_time, int tot_procs) {
    for (int i = 0; i < tot_procs; i++) {
        printf("Process %d was estimated for %d and took %d\n", i, est_time, temp_arr[i]);
    }
}

int calc_wait(int *temp_arr, int tot_procs) {
    int wait_time = 0;
    for (int i = 0; i < (tot_procs - 1); i++) {
        wait_time += temp_arr[i];
    }
    return wait_time;
}

int calc_ta(int *temp_arr, int tot_procs) {
    int total = 0;
    int wait_time = 0;

    for (int i = 0; i < (tot_procs - 1); i++) {
        wait_time += temp_arr[i];
    }

    for (int i = 0; i < tot_procs; i++) {
        total += temp_arr[i];
    }
    total += wait_time;
    return total;
}




void sjf(struct Process *p, int tot_ticks, int tot_procs) {
    int time = 0, ta_time = 0, tot_wait = 0;
    int *temp_arr = malloc(sizeof(int) * tot_procs);

    printf("==Shortest-Job-First==\n");
    for (int i = 0; i < tot_ticks; i++) {
        printf("Simulating %dth tick of processes at time %d\n", i, time);
        for (int j = 0; j < tot_procs; j++) {
            temp_arr[j] = p[j].t[i];
            time += p[j].t[i];
        }
        bubble_sort(temp_arr, tot_procs);
        print_sjf(temp_arr, tot_procs);
        tot_wait += calc_wait(temp_arr, tot_procs);
        ta_time += calc_ta(temp_arr, tot_procs);
    }

    printf("Turnaround time: %d\n", ta_time);

    printf("Waiting time: %d\n\n", tot_wait);

    free(temp_arr);
}

void sjf_live(struct Process *p, int tot_ticks, int tot_procs) {
    int time = 0, ta_time = 0, tot_wait = 0, est_time = 0, est_error = 0;
    int *temp_arr = malloc(sizeof(int) * tot_procs);

    printf("==Shortest-Job-First Live==\n");
    for (int i = 0; i < tot_ticks; i++) {
        printf("Simulating %dth tick of processes at time %d\n", i, time);
        for (int j = 0; j < tot_procs; j++) {
            temp_arr[j] = p[j].t[i];
            time += p[j].t[i];
        }
        bubble_sort(temp_arr, tot_procs);
        print_sjfl(temp_arr, est_time, tot_procs);
        tot_wait += calc_wait(temp_arr, tot_procs);
        ta_time += calc_ta(temp_arr, tot_procs);
    }
    printf("Turnaround time: %d\n", ta_time);
    printf("Waiting time: %d\n", tot_wait);
    printf("Estimation error: %d\n", est_error);
}

////////////////////////////////////////////////////////////////////////////////
//MAIN METHOD

int main(int argc, char* argv[]) {

    int tot_ticks = 0;
    int tot_procs = 0;

    //open file to read
    FILE* fp;
    char *input_file = argv[optind];
    fp = fopen(input_file, "r");
    if (fp == NULL) {
        printf("No file to load\n");
        return EXIT_FAILURE;
    }

    //get total ticks and total processes
    fscanf(fp, "%d", &tot_ticks);
    fscanf(fp, "%d", &tot_procs);

    //allocate an array of procs
    struct Process p[tot_procs];

    //create arrays for each process
    create_procs(fp, p, tot_procs, tot_ticks);

    //run sjf
    sjf(p, tot_ticks, tot_procs);
    //run sjf live
    sjf_live(p, tot_ticks, tot_procs);

    fclose(fp);

    return EXIT_SUCCESS;
}
