/**
 * @file      raycast.c
 * @brief     Functions for raycasting with the bresenham line algorithm
 * @author    8dcc
 *
 *
 * These functions are different from the line drawing ones because in there we
 * don't care about the direction of the line (left to right == right to left)
 * but in here we always want to start from the origin (x0,y0) to the
 * destination (x1,y1).
 */

#include <stdint.h>
#include "include/main.h"
#include "include/raycast.h"

static void raycast_x(int x0, int y0, int x1, int y1, int* out_x, int* out_y) {
    int dx = (x1 > x0) ? x1 - x0 : x0 - x1;
    int dy = (y1 > y0) ? y1 - y0 : y0 - y1;

    int x_step = (x1 > x0) ? 1 : -1;
    int y_step = (y1 > y0) ? 1 : -1;

    int diff = 2 * dy - dx;

    /* Previous point before hitting wall */
    int ray_x = *out_x;
    int ray_y = *out_y;

    int y = y0;
    for (int x = x0; (x1 > x0) ? x <= x1 : x >= x1; x += x_step) {
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
    int dy = (y1 > y0) ? y1 - y0 : y0 - y1;

    int x_step = (x1 > x0) ? 1 : -1;
    int y_step = (y1 > y0) ? 1 : -1;

    int diff = 2 * dx - dy;

    /* Previous point before hitting wall */
    int ray_x = *out_x;
    int ray_y = *out_y;

    int x = x0;
    for (int y = y0; (y1 > y0) ? y <= y1 : y >= y1; y += y_step) {
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

    /*
     * The raycast_x function will be used for angles from +45º to -45º
     * and from +135º to -135º:
     *
     * (+135º) .\   /. (+45º)
     *         ..\ /..
     *         ...X...
     *         ../ \..
     * (-135º) ./   \. (-45º)
     *
     *
     * The raycast_y function will be used for angles from +135º to +45º and
     * from -135º to -45º:
     *
     * (+135º) \...../ (+45º)
     *          \.../
     *           \./
     *            X
     *           /.\
     *          /...\
     * (-135º) /.....\ (-45º)
     */
    if (ABS(y1 - y0) < ABS(x1 - x0))
        raycast_x(x0, y0, x1, y1, out_x, out_y);
    else
        raycast_y(x0, y0, x1, y1, out_x, out_y);
}
