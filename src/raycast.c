/**
 * @file      raycast.c
 * @brief     Functions for raycasting with the bresenham line algorithm
 * @author    8dcc
 *
 *
 * These functions are different from the line drawing ones because in there we
 * don't care about the direction of the line (left to right == right to left)
 * but in here we always want to start from A to B.
 */

#include <stdint.h>
#include "include/main.h"
#include "include/raycast.h"

#define WALL 255

static vec2_t raycast_x(vec2_t a, vec2_t b) {
    int dx = (b.x > a.x) ? b.x - a.x : a.x - b.x;
    int dy = (b.y > a.y) ? b.y - a.y : a.y - b.y;

    int x_step = (b.x > a.x) ? 1 : -1;
    int y_step = (b.y > a.y) ? 1 : -1;

    int diff = 2 * dy - dx;

    /* Previous point before hitting wall */
    vec2_t prev = {
        .x = a.x,
        .y = a.y,
    };

    int y = a.y;
    for (int x = a.x; (b.x > a.x) ? x <= b.x : x >= b.x; x += x_step) {
        if (arr[y * ARR_W + x] == WALL)
            return prev;

        /* Save ray position for next iteration */
        prev.x = x;
        prev.y = y;

        if (diff > 0) {
            diff += 2 * (dy - dx);
            y += y_step;
        } else {
            diff += 2 * dy;
        }
    }

    /* We reached B without hitting a wall, return it */
    return b;
}

static vec2_t raycast_y(vec2_t a, vec2_t b) {
    int dx = (b.x > a.x) ? b.x - a.x : a.x - b.x;
    int dy = (b.y > a.y) ? b.y - a.y : a.y - b.y;

    int x_step = (b.x > a.x) ? 1 : -1;
    int y_step = (b.y > a.y) ? 1 : -1;

    int diff = 2 * dx - dy;

    /* Previous point before hitting wall */
    vec2_t prev = {
        .x = a.x,
        .y = a.y,
    };

    int x = a.x;
    for (int y = a.y; (b.y > a.y) ? y <= b.y : y >= b.y; y += y_step) {
        if (arr[y * ARR_W + x] == WALL)
            return prev;

        /* Save ray position for next iteration */
        prev.x = x;
        prev.y = y;

        if (diff > 0) {
            diff += 2 * (dx - dy);
            x += x_step;
        } else {
            diff += 2 * dx;
        }
    }

    /* We reached B without hitting a wall, return it */
    return b;
}

vec2_t raycast(vec2_t a, vec2_t b) {
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
    if (ABS(b.y - a.y) < ABS(b.x - a.x))
        return raycast_x(a, b);
    else
        return raycast_y(a, b);
}
