#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdbool.h>
#include "map.h"

bool            invalid_args(const int argc, const char *argv[]);
FILE            *open_file(const char *filename);
bool            parse_map(FILE *file, t_map *map);
bool            parse_line(char *line, t_map *map, const uint64_t line_count);

#endif