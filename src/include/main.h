#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#define ABS(n)     ((n) < 0 ? (-(n)) : (n))
#define DEG2RAD(X) ((X)*M_PI / 180.0f)
#define RAD2DEG(X) ((X)*180.0f / M_PI)

#define ARR_H 99
#define ARR_W 99

typedef struct {
    int x, y;
} vec2_t;

/* Values 0..255 represent brightness of each cell */
extern uint8_t arr[ARR_H * ARR_W];

static inline void set_val(int y, int x, uint8_t val) {
    arr[y * ARR_W + x] = val;
}

#endif /* MAIN_H_ */
