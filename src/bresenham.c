/**
 * @file      bresenham.c
 * @brief     Functions for drawing lines with the bresenham line algorithm
 * @author    8dcc
 */

#include <stdint.h>
#include "include/main.h"
#include "include/bresenham.h"
#include "include/rotation.h"

static void bresenham_x(vec2_t a, vec2_t b) {
    int dx = b.x - a.x;
    int dy = (b.y > a.y) ? b.y - a.y : a.y - b.y;

    int diff   = 2 * dy - dx;
    int y_step = (b.y > a.y) ? 1 : -1;

    int y = a.y;
    for (int x = a.x; x <= b.x; x++) {
        /* TODO: Color parameter */
        set_val(y, x, 100);

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
        /* TODO: Color parameter */
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

#define DRAW_ANGLE_STEP DEG2RAD(1.f)

void draw_angle(float deg, vec2_t vertex, vec2_t ang_center) {
    deg /= 2;

    /* Start and end points of our angle */
    vec2_t start = rotate_rel(DEG2RAD(-deg), vertex, ang_center);
    vec2_t end   = rotate_rel(DEG2RAD(deg), vertex, ang_center);

    /* Current point we are drawing, last drawn and rotated ammount in radians
     * since we started.  */
    vec2_t cur    = start;
    vec2_t prev   = start;
    float rotated = 0.f;

    /* Rotate until we reach the end */
    do {
        /* Draw current line of the angle.
         * TODO: Draw rectangles to fill empty points */
        bresenham_line(vertex, cur);

        /* Rotate by STEP until we get a different point */
        while (cur.x == prev.x && cur.y == prev.y) {
            rotated += DRAW_ANGLE_STEP;
            cur = rotate_rel(rotated, vertex, start);
        }

        /* Save new point for comparing in the next iteration */
        prev = cur;
    } while (prev.x != end.x || prev.y != end.y);
}
