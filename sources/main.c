#include "parse.h"
#include "point.h"
#include "map.h"
#include <stdlib.h>

bool	render(t_map map);

int main(int argc, const char *argv[])
{
    if (invalid_args(argc, argv))
        return (1);

    FILE    *file;
    t_map   map;

    file = open_file(argv[1]);
    if (!file)
        return (1);
    if (!parse_map(file, &map))
        return (1);
    if (!render(map))
        return (1);
    free(map.points);
    return (0);
}
