#include "map.h"
#include "projections.h"
#include <stdbool.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#define WIDTH 1920
#define HEIGHT 1080
#define ROW 0
#define COL 1

bool            render(t_map map);
static void     compute(t_vect2 *points, const t_map map);
static void     draw_lines(t_vect2 *points, const uint64_t width, const uint64_t height);

bool    render(t_map map)
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
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        projection_points = calloc(map.width * map.height, sizeof(t_vect2));
        if (!projection_points)
        {
            glfwTerminate();
            return (false);
        }
        compute(projection_points, map);
        draw_lines(projection_points, map.width, map.height);
        free(projection_points);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return (true);
}

static void compute(t_vect2 *points, const t_map map)
{
    uint64_t grid[2];

    grid[ROW] = 0;
    while (grid[ROW] < map.height)
    {
        grid[COL] = 0;
        while (grid[COL] < map.width)
        {
            points[grid[ROW] * map.width + grid[COL]] =
                isometric_projection(grid, map.points[grid[ROW] * map.width + grid[COL]].altitude);
            ++grid[COL];
        }
        ++grid[ROW];
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