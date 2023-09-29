/**
 * @file      bresenham.c
 * @brief     Functions for drawing lines with the bresenham line algorithm
 * @author    8dcc
 */

#include <stdint.h>
#include "include/main.h"
#include "include/bresenham.h"

static void bresenham_x(vec2_t a, vec2_t b) {
    int dx = b.x - a.x;
    int dy = (b.y > a.y) ? b.y - a.y : a.y - b.y;

    int diff   = 2 * dy - dx;
    int y_step = (b.y > a.y) ? 1 : -1;

    int y = a.y;
    for (int x = a.x; x <= b.x; x++) {
        /* TODO: Color */
        set_val(y, x, 120);

        if (diff > 0) {
            diff += 2 * (dy - dx);
            y += y_step;
        } else {
            diff += 2 * dy;
        }
    }
}

static void bresenham_y(vec2_t a, vec2_t b) {
    int dx = (b.x > a.x) ? b.x - a.x : a.x - b.x;
    int dy = b.y - a.y;

    int diff   = 2 * dx - dy;
    int x_step = (b.x > a.x) ? 1 : -1;

    int x = a.x;
    for (int y = a.y; y <= b.y; y++) {
        /* TODO: Color */
        set_val(y, x, 100);

        if (diff > 0) {
            diff += 2 * (dx - dy);
            x += x_step;
        } else {
            diff += 2 * dx;
        }
    }
}

void bresenham_line(vec2_t a, vec2_t b) {
    if (ABS(b.y - a.y) < ABS(b.x - a.x)) {
        if (b.x >= a.x)
            bresenham_x(a, b);
        else
            bresenham_x(b, a);
    } else {
        if (b.y >= a.y)
            bresenham_y(a, b);
        else
            bresenham_y(b, a);
    }
}
