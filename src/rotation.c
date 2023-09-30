
#include "include/main.h"
#include "include/rotation.h"
#include <math.h>

/* These could be function parameters, no point right now */
#define MAX_X (ARR_W - 1)
#define MAX_Y (ARR_H - 1)

void rotate(float rad_ang, vec2_t in, vec2_t* out) {
    out->x = in.x * cosf(rad_ang) - in.y * sinf(rad_ang);
    out->y = in.x * sinf(rad_ang) + in.y * cosf(rad_ang);
}

void rotate_rel(float rad_ang, vec2_t orig, vec2_t in, vec2_t* out) {
    /* Subtract in.y from orig.y because more Y means less index in array */
    const vec2_t rel = {
        .x = in.x - orig.x,
        .y = orig.y - in.y,
    };

    /* Rotate ralative */
    rotate(rad_ang, rel, out);

    /* Convert back to real array index */
    out->x = orig.x + out->x;
    out->y = orig.y - out->y;

    /* Clamp to make sure we are in array */
    out->x = CLAMP(out->x, 0, MAX_X);
    out->y = CLAMP(out->y, 0, MAX_Y);
}
