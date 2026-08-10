#include "fdf.h"
#include "parse.h"
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    if (invalid_args(argc, argv))
        return (1);

    FILE *file;
    t_context context;

    initialize_context(&context);
    file = open_file(argv[1]);
    if (!file)
        return (1);
    if (!parse_map(file, &context.map))
        return (1);
    initialize_camera(&context.camera);
    if (!render(context))
        return (1);
    free(context.map.points);
    return (0);
}
