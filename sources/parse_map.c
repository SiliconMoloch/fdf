#include "parse.h"
#include "map.h"
#include <stdlib.h>

bool    parse_map(FILE *file, t_map *map)
{
    char        *line;
    uint64_t    buffer_size;
    uint64_t    line_count;

    map->points = NULL;
    line = NULL;
    line_count = 0;
    map->width = 0;
    map->height = 0;
    while (getline(&line, &buffer_size, file) != -1)
    {
        if (!parse_line(line, map, ++line_count))
        {
            free(line);
            fclose(file);
            return (false);
        }
    }
    free(line);
    if (!ferror(file))
    {
        fclose(file);
        if (map->points)
        {
            map->height = line_count;
            if (!map->width || !map->height)
                fprintf(stderr, "Warning: The map is empty.\n");
        }
        else
            fprintf(stderr, "Warning: The map is empty.\n");
        return (true);
    }
    fclose(file);
    perror("getline()");
    return (false);
}