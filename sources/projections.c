#include "fdf.h"
#include "projections.h"

t_vect2 isometric_projection(t_context context, uint64_t grid[2], uint64_t point_position)
{
    t_vect2 p;
    const float x = (float)grid[X];
    const float y = (float)grid[Y];
    const float z = context.map.points[point_position].altitude * context.z_axis_scale;
    const float iso_x = (x - y) * cosf(ISO_ANGLE);
    const float iso_y = (x + y) * sinf(ISO_ANGLE);

    p.x =  iso_x;
    p.y = -iso_y + z;
    return (p);
}

#include <string.h>

t_vect2 conic_projection(t_context context, uint64_t grid[2], uint64_t point_position)
{
    t_vect2 p;
    const float x = (float)grid[X];
    const float y = (float)grid[Y];
    const float z = context.map.points[point_position].altitude * context.camera.zoom;
    const float iso_x = (x - y) * cosf(ISO_ANGLE);
    const float iso_y = (x + y) * sinf(ISO_ANGLE);

    p.x =  iso_x * context.camera.zoom + context.camera.position.x;
    p.y = -iso_y * context.camera.zoom + context.camera.position.y + z;
    return (p);
}

t_vect2 oblique_projection(t_context context, uint64_t grid[2], uint64_t point_position)
{
    t_vect2 p;
    const float x = (float)grid[X];
    const float y = (float)grid[Y];
    const float z = context.map.points[point_position].altitude * context.camera.zoom;
    const float iso_x = (x - y) * cosf(ISO_ANGLE);
    const float iso_y = (x + y) * sinf(ISO_ANGLE);

    p.x =  iso_x * context.camera.zoom + context.camera.position.x;
    p.y = -iso_y * context.camera.zoom + context.camera.position.y + z;
    return (p);
}