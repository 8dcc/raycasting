#ifndef BRESENHAM_H_
#define BRESENHAM_H_

#define ABS(n) ((n) < 0 ? (-(n)) : (n))

void bresenham_line(int x0, int y0, int x1, int y1);
void raycast_line(int x0, int y0, int x1, int y1, int* out_x, int* out_y);

#endif /* BRESENHAM_H_ */
