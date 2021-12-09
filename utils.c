#include "reutils.h"

Point PointAdd(Point p, int x, int y) {
	return (Point) { p.x + x, p.y + y };
}