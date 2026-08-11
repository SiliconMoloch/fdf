#include "fdf.h"
#include "projections.h"

t_vect2 isometric_projection(t_context context, uint64_t grid[2], uint64_t point_position)
{
    t_vect2     p;
    const float x = (float)grid[X];
    const float y = (float)grid[Y];
    const float z = context.map.points[point_position].altitude * context.z_axis_scale;

    p.x = (x - y) * cosf(ISO_ANGLE);
    p.y = (-x - y) * sinf(ISO_ANGLE) + z;
    return (p);
}

t_vect2 conic_projection(t_context context, uint64_t grid[2], uint64_t point_position)
{
    t_vect2 p;

    (void)context;
    (void)grid;
    (void)point_position;
    p.x = 0;
    p.y = 0;
    return (p);
}

t_vect2 oblique_projection(t_context context, uint64_t grid[2], uint64_t point_position)
{
    t_vect2     p;
    const float x = (float)grid[X];
    const float y = (float)grid[Y];
    const float z = context.map.points[point_position].altitude * context.z_axis_scale;

    p.x = x + z * cosf(OBLIQUE_ANGLE);
    p.y = -y + z * sinf(OBLIQUE_ANGLE);
    return (p);
}