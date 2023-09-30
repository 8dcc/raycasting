/**
 * @file      bresenham.c
 * @brief     Functions for drawing lines with the bresenham line algorithm
 * @author    8dcc
 */

#include <stdint.h>
#include "include/main.h"
#include "include/bresenham.h"
#include "include/raycast.h"
#include "include/rotation.h"

static void bresenham_x(vec2_t a, vec2_t b, color_t col) {
    int dx = b.x - a.x;
    int dy = (b.y > a.y) ? b.y - a.y : a.y - b.y;

    int diff   = 2 * dy - dx;
    int y_step = (b.y > a.y) ? 1 : -1;

    int y = a.y;
    for (int x = a.x; x <= b.x; x++) {
        set_val(y, x, col);

        if (diff > 0) {
            diff += 2 * (dy - dx);
            y += y_step;
        } else {
            diff += 2 * dy;
        }
    }
}

static void bresenham_y(vec2_t a, vec2_t b, color_t col) {
    int dx = (b.x > a.x) ? b.x - a.x : a.x - b.x;
    int dy = b.y - a.y;

    int diff   = 2 * dx - dy;
    int x_step = (b.x > a.x) ? 1 : -1;

    int x = a.x;
    for (int y = a.y; y <= b.y; y++) {
        set_val(y, x, col);

        if (diff > 0) {
            diff += 2 * (dx - dy);
            x += x_step;
        } else {
            diff += 2 * dx;
        }
    }
}

void bresenham_line(vec2_t a, vec2_t b, color_t col) {
    if (ABS(b.y - a.y) < ABS(b.x - a.x)) {
        if (b.x >= a.x)
            bresenham_x(a, b, col);
        else
            bresenham_x(b, a, col);
    } else {
        if (b.y >= a.y)
            bresenham_y(a, b, col);
        else
            bresenham_y(b, a, col);
    }
}

void draw_raycast(vec2_t start, vec2_t end, color_t col) {
    vec2_t cast = raycast(start, end);
    bresenham_line(start, cast, col);
}

#define DRAW_ANGLE_STEP DEG2RAD(0.1f)

void draw_angle(float deg, vec2_t vertex, vec2_t ang_center, color_t col) {
    /* Start and end points of our angle */
    vec2_t start = rotate_rel(DEG2RAD(-(deg / 2)), vertex, ang_center);

    /* Ammount of radians we want to rotate */
    const float target_rad = DEG2RAD(deg);

    /* Current point we are drawing and last point we drawed */
    vec2_t cur  = start;
    vec2_t prev = start;

    /* Rotate until we reach the end */
    float rotated = 0.f;
    while (rotated < target_rad) {
        /* Draw current line of the angle.
         * TODO: Draw rectangles to fill empty points */
        bresenham_line(vertex, cur, col);

        /* Rotate by STEP until we get a different point */
        while (cur.x == prev.x && cur.y == prev.y) {
            rotated += DRAW_ANGLE_STEP;
            cur = rotate_rel(rotated, vertex, start);
        }

        /* Save new point for comparing in the next iteration */
        prev = cur;
    }
}
