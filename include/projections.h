#ifndef PROJECTIONS_H
#define PROJECTIONS_H

#define ISO_ANGLE (M_PI / 6.f)

#include "vector.h"
#include <stdint.h>
#include <math.h>

t_vect2  isometric_projection(uint64_t grid[2], int64_t altitude);

#endif