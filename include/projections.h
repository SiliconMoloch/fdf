#ifndef PROJECTIONS_H
#define PROJECTIONS_H

#define ISO_ANGLE (M_PI / 6.f)
#define ZOOM_FACTOR 0.40f

#include "vector.h"
#include <stdint.h>
#include <math.h>

t_vect2 isometric_projection(t_context context, uint64_t grid[2], uint64_t point_position);
t_vect2 conic_projection(t_context context, uint64_t grid[2], uint64_t point_position);
t_vect2 oblique_projection(t_context context, uint64_t grid[2], uint64_t point_position);

#endif