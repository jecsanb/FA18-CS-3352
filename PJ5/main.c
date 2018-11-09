#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Jecsan Blanco
 * 2018FA OP SYSTEMS & NETWRK (CS-3352-01)
 * Programming Assignment #05
 *
 * Write a C Linux program to calculate the sum and maximum of two inputed
 * numbers. Two inputted numbers should be typed in from the keyboard.
 * On thread will calculate the sum of the two inputs. The other thread
 * will find the maximum value of the inputted numbers.
 */

struct SumNums {
    int a;
    int b;
    int sum;
    int max;
};

/* this function is run by the second thread
 * gets the max(a,b) stored back in the the max var in struct*/

void *max(void *vals) {
    struct SumNums *nums = (struct SumNums *) vals;
    nums->max = (nums->a > nums->b) ? nums->a : nums->b;
    return  NULL;
}

/* this function is run by the first thread
* gets the sum( a,b) stored back in the the sum var in struct*/
void *sum(void *vals) {
    /* increment x to 100 */
    struct SumNums *nums = (struct SumNums *) vals;
    nums->sum = nums->a + nums->b;
    return NULL;
}

int main(int argc, char **argv) {
    int input[3];
    if (argc < 2) {

        printf("Enter the first number: ");
        scanf("%d", &input[0]);

        printf("Enter the second number: ");
        scanf("%d", &input[1]);
    } else {
        char *ptr;
        input[0] = (int) strtol(argv[1], &ptr, 10);
        input[1] = (int) strtol(argv[2], &ptr, 10);
    }

    struct SumNums num = {input[0], input[1], 0};
    pthread_t sum_x_y_thread;
    /* create a second thread which executes inc_x(&x) */
    if (pthread_create(&sum_x_y_thread, NULL, sum, &num)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    pthread_t max_thread;
    /* create a second thread which executes inc_x(&x) */
    if (pthread_create(&max_thread, NULL, max, &num)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* wait for the second thread to finish */
    if (pthread_join(max_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    printf("Enter the first number: %d\n", num.a);
    printf("Enter the second number: %d\n", num.b);
    printf("The sum of the two numbers from thread one is: %d\n", num.sum);
    printf("The maximum of the two numbers from thread one is: %d\n", num.max);
    return 0;
}