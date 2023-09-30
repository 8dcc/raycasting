#ifndef ROTATION_H_
#define ROTATION_H_

#include "main.h"

/**
 * @brief Get rotated position from rotation matrix
 * @details Asumes the vertex of the angle is (0,0). See rotate_rel()
 * @param[in] rad_ang The angle to rotate in radians
 * @param[in] in Point to rotate
 * @return Rotated point
 */
vec2_t rotate(float rad_ang, vec2_t in);

/**
 * @brief Get rotated position of point relative to the vertex
 * @param[in] rad_ang The angle to rotate in radians
 * @param[in] vertex Vertex of the angle
 * @param[in] in Point to rotate
 * @return Rotated point relative to vertex
 */
vec2_t rotate_rel(float rad_ang, vec2_t vertex, vec2_t in);

#endif /* ROTATION_H_ */
