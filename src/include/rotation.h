#ifndef ROTATION_H_
#define ROTATION_H_

#include "main.h"

void rotate(float rad_ang, vec2_t in, vec2_t* out);
void rotate_rel(float rad_ang, vec2_t orig, vec2_t in, vec2_t* out);

#endif /* ROTATION_H_ */
