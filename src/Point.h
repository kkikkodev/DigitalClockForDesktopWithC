#ifndef _POINT_H
#define _POINT_H

typedef struct _point{
	int x;
	int y;
}Point;

Point Point_Create(int x, int y);
const int Point_GetX(Point point);
const int Point_GetY(Point point);

#endif