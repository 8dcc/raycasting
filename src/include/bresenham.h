#ifndef BRESENHAM_H_
#define BRESENHAM_H_

/**
 * @brief Draw a line in the global array using the bresenham's line algorithm
 * @details Uses the set_val inline function from main.h
 * @param[in] a Start of line
 * @param[in] b End of line
 */
void bresenham_line(vec2_t a, vec2_t b);

/**
 * @brief Draws an angle cone of X degrees from an origin to another point
 * @param[in] deg Angle to draw in degrees, not radians
 * @param[in] vertex Vertex of the angle
 * @param[in] ang_center The position at the center of the angle
 */
void draw_angle(float deg, vec2_t vertex, vec2_t ang_center);

#endif /* BRESENHAM_H_ */
