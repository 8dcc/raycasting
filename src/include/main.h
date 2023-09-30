#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include <math.h> /* M_PI */

#ifdef DEBUG
#include <stdio.h>
#endif

#define ABS(N)     ((N) < 0 ? (-(N)) : (N))
#define DEG2RAD(X) ((X)*M_PI / 180.0f)
#define RAD2DEG(X) ((X)*180.0f / M_PI)
#define MAX(A, B)  ((A) < (B) ? B : A)
#define MIN(A, B)  ((A) > (B) ? B : A)
#define CLAMP(VAL, MIN, MAX) \
    (((VAL) > (MAX)) ? (MAX) : (((VAL) < (MIN)) ? (MIN) : (VAL)))

#define ARR_H 99
#define ARR_W 99

#define FOV 90.f

typedef struct {
    int32_t x, y;
} vec2_t;

/**
 * @var arr
 * @brief Global array. Values 0..255 represent brightness of each cell
 */
extern uint8_t arr[ARR_H * ARR_W];

/**
 * @brief Set a value inside the global array
 * @param[in] y, x Position
 * @param[in] val Value from 0 to 255
 */
static inline void set_val(int y, int x, uint8_t val) {
#ifdef DEBUG
    if (y >= ARR_H || x >= ARR_W)
        fprintf(stderr, "set_val: Writing out of bounds (%d, %d)\n", y, x);
#endif

    arr[y * ARR_W + x] = val;
}

#endif /* MAIN_H_ */
