
#include <stdint.h>
#include <stdio.h>
#include "include/main.h"
#include "include/bresenham.h"

uint8_t arr[ARR_H * ARR_W] = { 0 };

/* TODO: SDL */
void print_arr(void) {
    putchar('+');
    for (int x = 0; x < ARR_W; x++)
        putchar('-');
    printf("+\n");

    for (int y = 0; y < ARR_H; y++) {
        putchar('|');

        for (int x = 0; x < ARR_W; x++) {
            if (arr[y * ARR_W + x] <= 0)
                putchar(' ');
            else
                putchar('*');
        }

        printf("|\n");
    }

    putchar('+');
    for (int x = 0; x < ARR_W; x++)
        putchar('-');
    printf("+\n");
}

int main(int argc, char** argv) {
    bresenham_line(3, 3, 10, 15);
    print_arr();

    return 0;
}
