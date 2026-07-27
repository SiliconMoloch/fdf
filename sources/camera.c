#include "camera.h"

void initialize_camera(t_camera *camera)
{
    camera->position.x = 0.0f;
    camera->position.y = 0.0f;
    camera->zoom = 0.05f;
}