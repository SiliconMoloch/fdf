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
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        (*context).camera.position.y += step;
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        (*context).camera.position.y -= step;
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        (*context).camera.position.x -= step;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        (*context).camera.position.x += step;
}

void    scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    t_context   *context;
    const float zoom_step = 0.1f;

    context = (t_context *)glfwGetWindowUserPointer(window);
    (void)xoffset;
    if (yoffset > 0)
        (*context).camera.zoom += zoom_step;
    else if (yoffset < 0)
        (*context).camera.zoom -= zoom_step;
}