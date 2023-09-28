/**
 * @file      bresenham.c
 * @brief     Bresenham line functions
 * @author    8dcc
 */

#include <stdint.h>
#include "include/bresenham.h"
#include "include/main.h"

static void bresenham_x(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = (y1 > y0) ? y1 - y0 : y0 - y1;

    int diff   = 2 * dy - dx;
    int y_step = (y1 > y0) ? 1 : -1;

    int y = y0;
    for (int x = x0; x < x1; x++) {
        set_val(y, x, 255);

        if (diff > 0) {
            diff += 2 * (dy - dx);
            y += y_step;
        } else {
            diff += 2 * dy;
        }
    }
}

static void bresenham_y(int x0, int y0, int x1, int y1) {
    int dx = (x1 > x0) ? x1 - x0 : x0 - x1;
    int dy = y1 - y0;

    int diff   = 2 * dx - dy;
    int x_step = (x1 > x0) ? 1 : -1;

    int x = x0;
    for (int y = y0; y < y1; y++) {
        set_val(y, x, 255);

        if (diff > 0) {
            diff += 2 * (dx - dy);
            x += x_step;
        } else {
            diff += 2 * dx;
        }
    }
}

void bresenham_line(int x0, int y0, int x1, int y1) {
    if (ABS(y1 - y0) < ABS(x1 - x0)) {
        if (x1 >= x0)
            bresenham_x(x0, y0, x1, y1);
        else
            bresenham_x(x1, y1, x0, y0);
    } else {
        if (y1 >= y0)
            bresenham_y(x0, y0, x1, y1);
        else
            bresenham_y(x1, y1, x0, y0);
    }
}
