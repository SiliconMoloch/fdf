#include "projections.h"
#define X 0
#define Y 1

t_vect2 isometric_projection(uint64_t grid[2], int64_t altitude)
{
    t_vect2 p;
    float   points[2];

    points[X] = (float)grid[X];
    points[Y] = (float)grid[Y];

    p.x = (points[X] - points[Y]) * cos(ISO_ANGLE);
    p.y = (points[X] + points[Y]) * sin(ISO_ANGLE) + altitude;
    p.x *= 0.05f;
    p.y *= 0.05f;
    return (p);
}