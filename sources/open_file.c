#include "parse.h"

FILE    *open_file(const char *filename)
{
    FILE    *file;

    file = fopen(filename, "r");
    if (file)
        return (file);
    perror("fopen()");
    fprintf(stderr, "Usage: ./fdf <filename.fdf>\n");
    return (NULL);
}
