#include "parse.h"
#include <string.h>

bool            invalid_args(const int argc, const char *argv[]);
static bool     fdf_file(const char *filename);

bool invalid_args(const int argc, const char *argv[])
{
    if (argc != 2 || !fdf_file(argv[1]))
    {
        fprintf(stderr, "Usage: ./fdf <filename.fdf>\n");
        return (true);
    }
    return (false);
}

static bool fdf_file(const char *argument)
{
    uint64_t  argument_length;

    argument_length = strlen(argument);
    if (argument_length < 4 || strcmp(argument + argument_length - 4, ".fdf"))
        return (false);
    return (true);
}