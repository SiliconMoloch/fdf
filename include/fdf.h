#ifndef FDF_H
#define FDF_H

#include <stdbool.h>
#include "map.h"
#include "camera.h"
#define WIDTH 1920
#define HEIGHT 1080
#define ROW 0
#define COL 1

typedef struct s_context
{
    t_map       map;
    t_point     *projected_points;
    t_camera    camera;
}   t_context;

bool    render(t_context context);

#endif