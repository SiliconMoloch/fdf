#ifndef POINT_H
#define POINT_H

#include <stdint.h>

typedef struct s_point
{
    int32_t altitude;
    union u_color
    {
        uint32_t u_color;
        struct
        {
            uint8_t b;
            uint8_t g;
            uint8_t r;
            uint8_t a;
        };
    }   t_color;
}   t_point;

#endif