#include "parse.h"
#include "map.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

bool                parse_line(char *line, t_map *map, const uint64_t line_count);
static bool         insert_value(char *line, t_point *point);
uint64_t            count_points(const char *line);

bool    parse_line(char *line, t_map *map, const uint64_t line_count)
{
    const uint64_t    expected_nb_points = count_points(line);
    t_point           *new_points;

    if (!map->points)
    {
        map->width = expected_nb_points;
        map->points = calloc(map->width, sizeof(t_point));
        if (!map->points)
        {
            perror("calloc()");
            return (false);
        }
        if (!insert_value(line, map->points))
        {
            free(map->points);
            return (false);
        }
    }
    else if (map->width != expected_nb_points)
    {
        free(map->points);
        fprintf(stderr, "Error: line %lu has a inconsistent number of points than the previous lines\n-> %s\n", line_count, line);
        return (false);
    }
    else
    {
        new_points = realloc(map->points, line_count * map->width * sizeof(t_point));
        if (!new_points)
        {
            free(map->points);
            perror("realloc()");
            return (false);
        }
        map->points = new_points;
        if (!insert_value(line, &map->points[(line_count - 1) * map->width]))
        {
            free(map->points);
            return (false);
        }
    }
    return (true);
}

static bool    insert_value(char *line, t_point *point)
{
    int64_t     altitude;
    char        *end_pointer;

    while (*line)
    {
        while (isspace(*line))
            ++line;
        if (!*line)
            break;
        errno = 0;
        altitude = strtol(line, &end_pointer, 10);
        if (errno == ERANGE)
        {
            fprintf(stderr, "Error: altitude value %ld is out of range\n", altitude);
            return (false);
        }
        point->altitude = (int32_t)altitude;
        if (*end_pointer == ',')
            point->t_color.u_color = strtoul(end_pointer + 1, &end_pointer, 16);
        else if (*end_pointer == ' ' || *end_pointer == '\n' || *end_pointer == '\0')
            point->t_color.u_color = 0xFFFFFFFF;
        else if (errno == ERANGE)
        {
            fprintf(stderr, "Error: color value %u is out of range\n", point->t_color.u_color);
            return (false);
        }
        else
        {
            fprintf(stderr, "Error: invalid character '%c' in line\n-> %s\n", *end_pointer, line);
            return (false);
        }
        ++point;
        line = end_pointer;
    }
    return (true);
}

uint64_t    count_points(const char *line)
{
    uint64_t    count;

    count = 0;
    while (*line)
    {
        while (isspace(*line))
            ++line;
        if (!*line || *line == '\n')
            break;
        ++count;
        while (*line && !isspace(*line))
                ++line;
    }
    return (count);
}