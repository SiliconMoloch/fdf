#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "GLFW/glfw3.h"

void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void    scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif