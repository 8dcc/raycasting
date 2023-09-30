#ifndef ROTATION_H_
#define ROTATION_H_

#include "main.h"

/**
 * @brief Get rotated position from rotation matrix
 * @details Asumes the point is relative to (0,0). See rotate_rel()
 * @param[in] rad_ang The angle to rotate in radians
 * @param[in] in Point to rotate
 * @return Rotated point
 */
vec2_t rotate(float rad_ang, vec2_t in);

/**
 * @brief Get rotated position of point relative to another point
 * @details The `in` point should be relative to `orig`.
 * @param[in] rad_ang The angle to rotate in radians
 * @param[in] orig Origin when rotating. In rotate(), this would be (0,0)
 * @param[in] in Point to rotate
 * @return Rotated point
 */
vec2_t rotate_rel(float rad_ang, vec2_t orig, vec2_t in);

#endif /* ROTATION_H_ */
