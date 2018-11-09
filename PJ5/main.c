#include <pthread.h>
#include <stdio.h>

struct SumNums {
    int a;
    int b;
    int sum;
    int max;
};

void *max(void *vals) {
    struct SumNums *nums = (struct SumNums *) vals;
    nums->max = (nums->a > nums->b) ? nums->a : nums->b;
}

/* this function is run by the second thread */
void *sum(void *vals) {
    /* increment x to 100 */
    struct SumNums *nums = (struct SumNums *) vals;
    nums->sum = nums->a + nums->b;
    return NULL;
}

int main() {
    int input[3];
    printf("Enter the first number: ");
    scanf("%d",&input[0]);
    printf("Enter the second number: ");
    scanf("%d",&input[1]);
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