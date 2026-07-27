#ifndef PROJECTIONS_H
#define PROJECTIONS_H

#define ISO_ANGLE (M_PI / 6.f)

#include "vector.h"
#include <stdint.h>
#include <math.h>

t_vect2 isometric_projection(t_context context, uint64_t grid[2], uint64_t point_position);

#endif