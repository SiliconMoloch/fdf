#ifndef MAP_H
#define MAP_H

#include "point.h"

typedef struct s_map
{
    uint64_t width;
    uint64_t height;
    t_point *points;
}   t_map;

#endif