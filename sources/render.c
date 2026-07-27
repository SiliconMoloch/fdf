#include "fdf.h"
#include "callbacks.h"
#include "projections.h"
#include <stdlib.h>

bool            render(t_context context);
static void     compute(t_vect2 *points, const t_context context);
static void     draw_lines(t_vect2 *points, const uint64_t width, const uint64_t height);

bool    render(t_context context)
{
    GLFWwindow  *window;
    t_vect2     *projection_points;

    glfwInit();
    window = glfwCreateWindow(WIDTH, HEIGHT, "fdf", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return (false);
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, &context);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    projection_points = calloc(context.map.width * context.map.height, sizeof(t_vect2));
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        if (!projection_points)
        {
            glfwTerminate();
            return (false);
        }
        compute(projection_points, context);
        draw_lines(projection_points, context.map.width, context.map.height);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    free(projection_points);
    glfwTerminate();
    return (true);
}

static void compute(t_vect2 *points, const t_context context)
{
    uint64_t grid[2];
    uint64_t point_position;

    grid[Y] = 0;
    while (grid[Y] < context.map.height)
    {
        grid[X] = 0;
        while (grid[X] < context.map.width)
        {
            point_position = grid[Y] * context.map.width + grid[X];
            points[point_position] =
                isometric_projection(context, grid, point_position);
            ++grid[X];
        }
        ++grid[Y];
    }
}

static void draw_lines(t_vect2 *points, const uint64_t width, const uint64_t height)
{
    uint64_t x;
    uint64_t y;

    y = 0;
    glBegin(GL_LINES);
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            if (x < width - 1)
            {
                glVertex2f(points[y * width + x].x, points[y * width + x].y);
                glVertex2f(points[y * width + x + 1].x, points[y * width + x + 1].y);
            }
            if (y < height - 1)
            {
                glVertex2f(points[y * width + x].x, points[y * width + x].y);
                glVertex2f(points[(y + 1) * width + x].x, points[(y + 1) * width + x].y);
            }
            ++x;
        }
        ++y;
    }
    glEnd();
}