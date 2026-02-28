#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "status.hpp"
#include "json.hpp"
#include "geometry.hpp"
#include "io.hpp"
#include "draw.hpp"

typedef enum
{
    JSON_LOAD,
    FIND_SOLUTION,
    DRAW_SCALED_SOLUTION,
    DRAW_SOLUTION_ALL_POINTS
} request_type_t;


typedef struct
{
    request_type_t type;
    draw_scene_t scene;
    union
    {
        const char *filename;
    };

} request_t;

status_t manager(request_t &request);

#endif