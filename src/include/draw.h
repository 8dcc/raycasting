#ifndef DRAW_H_
#define DRAW_H_

/* Declared in bresenham.c */
typedef void (*drawfunc_t)(vec2_t a, vec2_t b, color_t col);
extern drawfunc_t fnDrawLine;

/**
 * @brief Draw a line in the global array using the bresenham's line algorithm
 * @details Uses the set_val inline function from main.h
 * @param[in] a Start of line
 * @param[in] b End of line
 * @param[in] col Color of the line
 */
void draw_line(vec2_t a, vec2_t b, color_t col);

/**
 * @brief Draw a line in the global array and fill empty gaps in adjacent cells
 * @details While drawing the line from A to B, it will check if the adjacent
 * tiles are empty, and if they are, it will check if they are surrounded by
 * filled cells. If it is, it will fill it as well.
 *
 * Useful for filling empty gaps in draw_angle()
 * @param[in] a Start of line
 * @param[in] b End of line
 * @param[in] col Color of the line
 */
void draw_line_and_fill(vec2_t a, vec2_t b, color_t col);

/**
 * @brief Cast a ray from start to end, and draw a line to the returned value
 * @details Uses the raycast() function
 * @param[in] start Start of ray
 * @param[in] end End of ray
 * @param[in] col Color of the line
 */
void draw_raycast(vec2_t start, vec2_t end, color_t col);

/**
 * @brief Cast a ray from start to end, draw a line to the returned value, and
 * fill adjacent empty cells
 * @details Same as draw_raycast() but uses draw_line_and_fill() instead of
 * draw_line()
 * @param[in] start Start of ray
 * @param[in] end End of ray
 * @param[in] col Color of the line
 */
void draw_raycast_and_fill(vec2_t start, vec2_t end, color_t col);

/**
 * @brief Draws an angle cone of X degrees from an origin to another point
 * @param[in] deg Angle to draw in degrees, not radians
 * @param[in] vertex Vertex of the angle
 * @param[in] ang_center The position at the center of the angle
 * @param[in] col Color of the line
 */
void draw_angle(float deg, vec2_t vertex, vec2_t ang_center, color_t col);

/**
 * @brief Raycasts an angle cone of X degrees from an origin to another point
 * @defails Same as draw_angle() but uses draw_raycast() instead of
 * draw_line_and_fill()
 * @param[in] deg Angle to draw in degrees, not radians.
 * @param[in] vertex Vertex of the angle
 * @param[in] ang_center The position at the center of the angle
 * @param[in] col Color of the line
 */
static inline void draw_raycast_angle(float deg, vec2_t vertex,
                                      vec2_t ang_center, color_t col) {
    drawfunc_t old = fnDrawLine;
    fnDrawLine     = draw_raycast_and_fill;
    draw_angle(deg, vertex, ang_center, col);
    fnDrawLine = old;
}

#endif /* DRAW_H_ */
