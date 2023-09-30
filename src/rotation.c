/**
 * @file      rotation.c
 * @brief     Functions for calculating points with rotation matrices
 * @author    8dcc
 */

#include "include/main.h"
#include "include/rotation.h"
#include <math.h>

/* These could be function parameters, no point right now */
#define MAX_X (ARR_W - 1)
#define MAX_Y (ARR_H - 1)

vec2_t rotate(float rad_ang, vec2_t in) {
    return (vec2_t){
        .x = in.x * cosf(rad_ang) - in.y * sinf(rad_ang),
        .y = in.x * sinf(rad_ang) + in.y * cosf(rad_ang),
    };
}

vec2_t rotate_rel(float rad_ang, vec2_t vertex, vec2_t in) {
    /* Subtract in.y from vertex.y because more Y means less index in array */
    const vec2_t rel = {
        .x = in.x - vertex.x,
        .y = vertex.y - in.y,
    };

    /* Rotate ralative */
    vec2_t ret = rotate(rad_ang, rel);

    /* Convert back to real array index */
    ret.x = vertex.x + ret.x;
    ret.y = vertex.y - ret.y;

    /* Clamp to make sure we are in array */
    ret.x = CLAMP(ret.x, 0, MAX_X);
    ret.y = CLAMP(ret.y, 0, MAX_Y);

    return ret;
}
