#include "map.h"
#include "vector.h"
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#define X 0
#define Y 1
#define Z 2
#define WIDTH 1920
#define HEIGHT 1080
#define ISO_ANGLE (M_PI / 6.f)

bool            render(t_map map);
//static void     draw(t_map map, t_vect2 *isometric_points);
static t_vect2  *parse_points(const uint64_t map_height, const uint64_t map_width, t_point *points);
static t_vect2  isometric_projection(uint64_t grid[2], int64_t altitude);

bool    render(t_map map)
{
    t_vect2 *isometric_points;

    isometric_points = parse_points(map.height, map.width, map.points);
    if (!isometric_points)
    {
        free(map.points);
        return (false);
    }
    //draw(map, isometric_points);
    free(isometric_points);
    return (true);
}

static t_vect2  *parse_points(const uint64_t map_height,  const uint64_t map_width, t_point *points)
{
    uint64_t grid[2];
    t_vect2 *isometric_points;

    isometric_points = calloc(map_width * map_height, sizeof(t_vect2));
    if (!isometric_points)
        return (NULL);
    grid[X] = 0;
    while (grid[X] < map_height)
    {
        grid[Y] = 0;
        while (grid[Y] < map_width)
        {
            isometric_points[grid[X] * map_width + grid[Y]] =
                isometric_projection(grid, points[grid[X] * map_width + grid[Y]].altitude);
            ++grid[Y];
        }
        ++grid[X];
    }
    return (isometric_points);
}

static t_vect2 isometric_projection(uint64_t grid[2], int64_t altitude)
{
    t_vect2 isometric_point;

    isometric_point.x = (grid[X] - grid[Y]) * cos(ISO_ANGLE);
    isometric_point.y = (grid[X] + grid[Y]) * sin(ISO_ANGLE) - altitude;
    return (isometric_point);
}
