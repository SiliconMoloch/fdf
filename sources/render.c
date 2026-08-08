#include "fdf.h"
#include "callbacks.h"
#include "projections.h"
#include <stdlib.h>

bool        render(t_context context);
static void compute(t_vect2 *points, const t_context context);
static void draw_lines(const t_context context, t_vect2 *points);
static void set_color(const t_context context, uint64_t index);

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
        draw_lines(context, projection_points);
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
            switch (context.projection_mode)
            {
                case 0:
                    points[point_position] =
                        isometric_projection(context, grid, point_position);
                    break;
                case 1:
                    points[point_position] =
                        conic_projection(context, grid, point_position);
                    break;
                case 2:
                    points[point_position] =
                        oblique_projection(context, grid, point_position);
                    break;
                default:
                    points[point_position] =
                        isometric_projection(context, grid, point_position);
            }
            ++grid[X];
        }
        ++grid[Y];
    }
}

static void draw_lines(const t_context context, t_vect2 *points)
{
    uint64_t x;
    uint64_t y;

    y = 0;
    glBegin(GL_LINES);
    while (y < context.map.height)
    {
        x = 0;
        while (x < context.map.width)
        {
            if (x < context.map.width - 1)
            {
                set_color(context, y * context.map.width + x);
                glVertex2f(points[y * context.map.width + x].x, points[y * context.map.width + x].y);
                set_color(context, y * context.map.width + x + 1);
                glVertex2f(points[y * context.map.width + x + 1].x, points[y * context.map.width + x + 1].y);
            }
            if (y < context.map.height - 1)
            {
                set_color(context, y * context.map.width + x);
                glVertex2f(points[y * context.map.width + x].x, points[y * context.map.width + x].y);
                set_color(context, (y + 1) * context.map.width + x);
                glVertex2f(points[(y + 1) * context.map.width + x].x, points[(y + 1) * context.map.width + x].y);
            }
            ++x;
        }
        ++y;
    }
    glEnd();
}

static void set_color(const t_context context, uint64_t index)
{
    if (context.color_mode)
    {
        glColor4ub(
            context.map.points[index].t_color.r,
            context.map.points[index].t_color.g,
            context.map.points[index].t_color.b,
            context.map.points[index].t_color.a
        );
    }
    else
        glColor4ub(255, 255, 255, 255);
}