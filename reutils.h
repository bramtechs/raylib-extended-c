#ifndef RE_UTILS_H
#define RE_UTILS_H

#include "raylib.h"

typedef struct {
	int x;
	int y;
} Point;

Point PointAdd(Point p, int x, int y);

#endif // !RE_UTILS_H
