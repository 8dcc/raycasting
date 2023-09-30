#ifndef BRESENHAM_H_
#define BRESENHAM_H_

/**
 * @brief Draw a line in the global array using the bresenham's line algorithm
 * @details Uses the set_val inline function from main.h
 * @param[in] a Start of line
 * @param[in] b End of line
 */
void bresenham_line(vec2_t a, vec2_t b, color_t col);

/**
 * @brief Cast a ray from start to end, and draw a line to the returned value
 * @details Uses the raycast() function
 * @param[in] start Start of ray
 * @param[in] end End of ray
 */
void draw_raycast(vec2_t start, vec2_t end, color_t col);

/**
 * @brief Draws an angle cone of X degrees from an origin to another point
 * @param[in] deg Angle to draw in degrees, not radians
 * @param[in] vertex Vertex of the angle
 * @param[in] ang_center The position at the center of the angle
 */
void draw_angle(float deg, vec2_t vertex, vec2_t ang_center, color_t col);

#endif /* BRESENHAM_H_ */
