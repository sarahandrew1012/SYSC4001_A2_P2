#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int counter = 50;
    int cycle = 0;

    for (; ; cycle++) {
        if (counter % 3 == 0) {
            printf("Cycle number: %d - %d is a multiple of 3.\n", cycle, counter);
        } else {
            printf("Cycle number: %d\n", cycle);
        }
        counter--;
        usleep(50000);
    }
    return 0;
}