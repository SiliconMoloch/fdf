#ifndef FDF_H
#define FDF_H

#include <stdbool.h>
#include "map.h"
#include "camera.h"

#define X 0
#define Y 1

typedef struct s_context
{
    uint16_t    screen_dimensions[2];
    t_map       map;
    t_point     *projected_points;
    t_camera    camera;
    bool        color_mode;
    uint8_t     projection_mode;
    float       z_axis_scale;

}   t_context;

void    initialize_context(t_context *context);
bool    render(t_context context);

#endif