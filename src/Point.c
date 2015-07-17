#include "Point.h"

Point Point_Create(int x, int y){
	Point point = { x, y };
	return point;
}

const int Point_GetX(Point point){
	return point.x;
}

const int Point_GetY(Point point){
	return point.y;
}