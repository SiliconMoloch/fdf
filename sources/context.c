#include "fdf.h"

void initialize_context(t_context *context)
{
    context->screen_dimensions[0] = 800;
    context->screen_dimensions[1] = 600;
    context->color_mode = true;
    context->projection_mode = 0;
    context->z_axis_scale = 1.0f;
}