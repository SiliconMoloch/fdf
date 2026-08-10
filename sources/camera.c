#include "camera.h"

void initialize_camera(t_camera *camera)
{
    camera->position.x = 0.0f;
    camera->position.y = 0.0f;
    camera->zoom = 0.05f;
    camera->angle = 0;
}

void apply_camera_transformations(t_vect2 *point, t_camera camera)
{
    const float x = point->x;
    const float y = point->y;
    const float angle_rad = camera.angle * (ANGLE_RAD);

    point->x = (x * cosf(angle_rad) - y * sinf(angle_rad));
    point->y = (x * sinf(angle_rad) + y * cosf(angle_rad));
    point->x = (point->x * camera.zoom) + camera.position.x;
    point->y = (point->y * camera.zoom) + camera.position.y;
}