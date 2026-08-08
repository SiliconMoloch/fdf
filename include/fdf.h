#ifndef FDF_H
#define FDF_H

#include <stdbool.h>
#include "map.h"
#include "camera.h"
#define WIDTH 1920
#define HEIGHT 1080
#define X 0
#define Y 1

typedef struct s_context
{
    t_map       map;
    t_point     *projected_points;
    t_camera    camera;
    bool        color_mode;
    uint8_t     projection_mode;
}   t_context;

bool    render(t_context context);

#endif