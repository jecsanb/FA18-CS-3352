/**
 * Jecsan Blanco
 * 2018FA OP SYSTEMS & NETWRK (CS-3352-01)
 * Project 4 - Partial manual input output.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#define SPACE  0x20
#define NL   0x0A


int countDigit(int n);

int charToInt(char c);

int strToInt(char *str);

void printLn(char *str);

void print(char *str);

void print(char *str) {
    write(1, str, strlen(str) * sizeof(char));
}

void printLn(char *str) {
    write(1, str, strlen(str) * sizeof(char));
    write(1, "\n", sizeof(char));
}


int countDigit(int n) {
    n = abs(n);
    return (n) ? (int) ((floor(log10(n))) + 1) : 1;
}

/**
 *  Converts any digit [0-9] into its ascii representation.
 */
char intToChar(int n) {
    assert(n >= 0 && n < 10);
    return (char) (n + 0x30);
}


/**
 * A integer into its null terminated string representation.
 */
char *intToStr(int num) {
    int sign = num < 0;
    int digits = countDigit(num);
    int charsNeeded = digits + sign + 1; // 1 for the \00
    char *string = malloc((charsNeeded) * sizeof(char));
    // handle negatives
    if (sign) {
        string[0] = '-';
        num = abs(num);
    }
    int v = 0;
    for (int i = charsNeeded - 2; i >= 0 + sign; --i) {
        v = num % 10;
        string[i] = intToChar(v);
        num /= 10;
    }
    string[charsNeeded - 1] = 0;
    return string;
}

/**
 * Turns a single ascii digit into its integer value.
 */
int charToInt(char c) {
    assert(c >= '0' && c <= '9');
    return c & 0x0F;
}

/**
 * Turns a null terminated string of ascii digits to its integer representation.
 */
int strToInt(char *str) {
    assert(str != NULL);
    int sign = (str[0] == '-') ? 1 : 0;
    if (sign) ++str;
    int digits = (int) strlen(str);

    int result = 0;
    int magnitude = 1;
    for (int i = digits - 1; i >= 0; --i) {
        result += charToInt(str[i]) * magnitude;
        magnitude *= 10;
    }
    //printf("At strToInt:%d\n",result);
    return (sign) ? result * -1 : result;
}

/**
 * Asks for two integers separated by a space to be added.
 */
int main(int argc, char *argv[]) {
    char *input_a = NULL, *input_b = NULL;
    char *output = NULL, *has_space = NULL;
    int input_allocated = 0;
    int result;
    size_t buffer_size = (sizeof(char) * 255);

    printLn("Enter two numbers on one line separated by a space.");
    if (argc >= 2) {
        // support for command line arguments in string format.
        input_a = argv[1];
        printLn(input_a);

    } else {
        input_allocated = 1;
        input_a = (char *) malloc(buffer_size);
        read(1, input_a, buffer_size);
        has_space = strchr(input_a,SPACE);
        if (has_space) {
            while(*has_space == SPACE){
               *has_space = 0;
               ++has_space;
            }
            input_b = has_space;
        }else{
            input_b = (char *) malloc(buffer_size);
            read(1, input_b ,buffer_size);

        }
        input_a[strcspn(input_a,"\n")] = 0;
        input_b[strcspn(input_b,"\n")] = 0;
    };

    //do the thing
    result = strToInt(input_a) + strToInt(input_b);
    //printf("Result of sum: %d",result);
    output = intToStr(result);
    //printf("Output:%s\n",output);
    print("Sum of the two numbers you entered = ");
    printLn(output);
    //Land of the
    free(output);
    if (input_allocated) free(input_a);
    return 0;
}
