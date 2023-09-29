/**
 * @file      raycast.c
 * @brief     Functions for raycasting with the bresenham line algorithm
 * @author    8dcc
 */

#include <stdint.h>
#include "include/main.h"
#include "include/raycast.h"

static void raycast_x(int x0, int y0, int x1, int y1, int* out_x, int* out_y) {
    int dx = x1 - x0;
    int dy = (y1 > y0) ? y1 - y0 : y0 - y1;

    int diff   = 2 * dy - dx;
    int y_step = (y1 > y0) ? 1 : -1;

    /* Previous point before hitting wall */
    int ray_x = *out_x;
    int ray_y = *out_y;

    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (arr[y * ARR_W + x] == 255) {
            *out_x = ray_x;
            *out_y = ray_y;
            return;
        }

        /* Save ray position for next iteration */
        ray_x = x;
        ray_y = y;

        if (diff > 0) {
            diff += 2 * (dy - dx);
            y += y_step;
        } else {
            diff += 2 * dy;
        }
    }
}

static void raycast_y(int x0, int y0, int x1, int y1, int* out_x, int* out_y) {
    int dx = (x1 > x0) ? x1 - x0 : x0 - x1;
    int dy = y1 - y0;

    int diff   = 2 * dx - dy;
    int x_step = (x1 > x0) ? 1 : -1;

    /* Previous point before hitting wall */
    int ray_x = *out_x;
    int ray_y = *out_y;

    int x = x0;
    for (int y = y0; y <= y1; y++) {
        if (arr[y * ARR_W + x] == 255) {
            *out_x = ray_x;
            *out_y = ray_y;
            return;
        }

        /* Save ray position for next iteration */
        ray_x = x;
        ray_y = y;

        if (diff > 0) {
            diff += 2 * (dx - dy);
            x += x_step;
        } else {
            diff += 2 * dx;
        }
    }
}

void raycast_line(int x0, int y0, int x1, int y1, int* out_x, int* out_y) {
    /* Default output if it doesn't hit a wall */
    *out_x = x1;
    *out_y = y1;

    /* FIXME: Use different functions for left to right */
    if (ABS(y1 - y0) < ABS(x1 - x0)) {
        if (x1 >= x0)
            raycast_x(x0, y0, x1, y1, out_x, out_y);
        else
            raycast_x(x1, y1, x0, y0, out_x, out_y);
    } else {
        if (y1 >= y0)
            raycast_y(x0, y0, x1, y1, out_x, out_y);
        else
            raycast_y(x1, y1, x0, y0, out_x, out_y);
    }
}
