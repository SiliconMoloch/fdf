#include "fdf.h"
#include "projections.h"

t_vect2 isometric_projection(t_context context, uint64_t grid[2], uint64_t point_position)
{
    t_vect2     p;
    float       points[2];
    const float altitude = context.map.points[point_position].altitude * context.camera.zoom;

    points[X] = (float)grid[X];
    points[Y] = (float)grid[Y];

    p.x = context.camera.zoom * (points[X] - points[Y]) * cos(ISO_ANGLE) + context.camera.position.x;
    p.y = context.camera.zoom * (points[X] + points[Y]) * sin(ISO_ANGLE) + context.camera.position.y + altitude;
    return (p);
}