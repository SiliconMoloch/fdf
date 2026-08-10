#ifndef CAMERA_H
#define CAMERA_H

# define ANGLE_RAD (M_PI / 180.0f)

#include <math.h>
#include "vector.h"
#include "point.h"

typedef struct s_camera
{
    t_vect2 position;
    float   zoom;
    float   angle;
}   t_camera;

void    initialize_camera(t_camera *camera);
void    apply_camera_transformations(t_vect2 *point, t_camera camera);

#endif