#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "status.hpp"
#include "json_process.hpp"
#include "points.hpp"
#include "geometry.hpp"
#include "io.hpp"
#include "draw.hpp"
#include "table.hpp"

typedef enum
{
    CLEAR_ALL,
    JSON_LOAD,
    SAVE_RESULT,
    CHANGE_POINT,
    ADD_NEW_POINT,
    DELETE_POINT,
    FIND_SOLUTION,
    FLUSH_POINTS_TO_TABLE,
    DRAW_SCALED_SOLUTION,
    DRAW_SOLUTION_ALL_POINTS
} request_type_t;


typedef struct
{
    request_type_t type;
    draw_scene_t scene;
    table_widget_t table_widget;
    point_t point;
    size_t point_id;
    const char *filename;

} request_t;

status_t manager(request_t &request);

#endif