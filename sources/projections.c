#include "fdf.h"
#include "projections.h"

#define OBLIQUE_ANGLE (25.0f * M_PI / 180.0f)
#define Z_SCALE 2.0f

t_vect2 isometric_projection(t_context context, uint64_t grid[2], uint64_t point_position)
{
    t_vect2 p;
    const float x = (float)grid[X];
    const float y = (float)grid[Y];
    const float z = context.map.points[point_position].altitude * context.camera.zoom * ZOOM_FACTOR;
    const float iso_x = (x - y) * cosf(ISO_ANGLE);
    const float iso_y = (x + y) * sinf(ISO_ANGLE);

    p.x =  iso_x * context.camera.zoom + context.camera.position.x;
    p.y = -iso_y * context.camera.zoom + context.camera.position.y + z;
    return (p);
}

#include <string.h>

t_vect2 conic_projection(t_context context, uint64_t grid[2], uint64_t point_position)
{
    t_vect2 p;

    bzero(&p, sizeof(t_vect2));
    (void)context;
    (void)grid;
    (void)point_position;
    return (p);
}

t_vect2 oblique_projection(t_context context, uint64_t grid[2], uint64_t point_position)
{
    t_vect2 p;
    const float x = (float)grid[X];
    const float y = (float)grid[Y];
    const float z = context.map.points[point_position].altitude * context.camera.zoom * ZOOM_FACTOR;
    const float oblique_x = x + y * cosf(OBLIQUE_ANGLE);
    const float oblique_y = y * sinf(OBLIQUE_ANGLE) - z * Z_SCALE;

    p.x = oblique_x * context.camera.zoom + context.camera.position.x;
    p.y = oblique_y * context.camera.zoom + context.camera.position.y;
    return (p);
}