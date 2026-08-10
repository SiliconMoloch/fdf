#include "fdf.h"
#include "callbacks.h"

void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    t_context   *context;
    const float step = 0.01f;

    context = (t_context *)glfwGetWindowUserPointer(window);
    (void)window;
    (void)scancode;
    (void)mods;
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            case GLFW_KEY_0:
                (*context).projection_mode = 0;
                break;
            case GLFW_KEY_1:
                (*context).projection_mode = 1;
                break;
            case GLFW_KEY_2:
                (*context).projection_mode = 2;
                break;
            case GLFW_KEY_W:
                (*context).camera.position.y += step;
                break;
            case GLFW_KEY_S:
                (*context).camera.position.y -= step;
                break;
            case GLFW_KEY_A:
                (*context).camera.position.x -= step;
                break;
            case GLFW_KEY_D:
                (*context).camera.position.x += step;
                break;
            case GLFW_KEY_UP:
                (*context).camera.angle += 5;
                break;
            case GLFW_KEY_DOWN:
                (*context).camera.angle -= 5;
                break;
            case GLFW_KEY_KP_ADD:
                (*context).z_axis_scale *= 1.1f;
                break;
            case GLFW_KEY_KP_SUBTRACT:
                (*context).z_axis_scale *= 0.9f;
                break;
            case GLFW_KEY_C:
                (*context).color_mode = !(*context).color_mode;
                break;

            default:
                break;
        }
    }
}

void    scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    t_context   *context;

    context = (t_context *)glfwGetWindowUserPointer(window);
    (void)xoffset;
    if (yoffset > 0)
        (*context).camera.zoom *= 1.1f;
    else if (yoffset < 0)
        (*context).camera.zoom *= 0.9f;
}