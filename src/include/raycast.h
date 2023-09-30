#ifndef RAYCAST_H_
#define RAYCAST_H_

/**
 * @brief Cast a ray from point A to point B
 * @details Uses the bresenhams line algorithm
 * @param[in] a Start of the ray
 * @param[in] b End of the ray
 * @return If it hits a wall, the position before hitting it. Otherwise, B.
 */
vec2_t raycast(vec2_t a, vec2_t b);

#endif /* RAYCAST_H_ */
