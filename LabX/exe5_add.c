#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

/*
 * This program implements two versions of add function:
 * add_v0: Takes exactly 3 integer references (as requested)
 * add_v1: Takes variable number of integer references
 */

// Version 0: Adds exactly 3 numbers by reference
int add_v0(int *a, int *b, int *c) {
    if(!a || !b || !c) {  // Check for NULL pointers
        fprintf(stderr, "Error: NULL pointer passed to add_v0\n");
        exit(EXIT_FAILURE);
    }
    return *a + *b + *c;
}

// Version 1: Adds variable number of integers by reference
int add_v1(int cnt_of_nums, ...) {
    va_list args;
    int *current;
    int sum = 0;

    va_start(args, cnt_of_nums);

    for(int i = 0; i < cnt_of_nums; i++) {
        current = va_arg(args, int*);
        if(!current) {  // Check if its NULL pointer
            fprintf(stderr, "Error: NULL pointer passed to add_v1\n");
            va_end(args);
            exit(EXIT_FAILURE);
        }
        sum += *current;
    }

    va_end(args);
    return sum;
}

int main() {
    srand(time(NULL));

    // Test add_v0
    int x = rand() % 50, y = rand() % 50, z = rand() % 50;
    printf("add_v0(%d, %d, %d) = %d\n", x, y, z, add_v0(&x, &y, &z));

    // Test add_v1
    printf("add_v1(3 numbers: %d, %d, %d) = %d\n", x, y, z, add_v1(3, &x, &y, &z));

    int a = rand() % 50, b = rand() % 50, c = rand() % 50, d = rand() % 50, e = rand() % 50;
    printf("add_v1(5 numbers: %d, %d, %d, %d, %d) = %d\n", a, b, c, d, e, add_v1(5, &a, &b, &c, &d, &e));

    return 0;
}
