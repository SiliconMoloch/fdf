 #ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "point.h"

typedef struct s_camera
{
    t_vect2 position;
    float   zoom;
}   t_camera;

void    initialize_camera(t_camera *camera);

#endif