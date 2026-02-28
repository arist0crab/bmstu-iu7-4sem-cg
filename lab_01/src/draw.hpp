#ifndef __DRAW_H__
#define __DRAW_H__

#include "status.hpp"
#include "json.hpp"
#include "geometry.hpp"
#include <QGraphicsScene>

const QColor ORDINARY_COLOR(123, 140, 123);
const QColor SOLUTION_COLOR(255, 94, 0);
const double SCENE_PADDING = 20;
const double POINT_RADIUS = 3;

typedef struct
{
    QGraphicsScene *scene;
    double width;
    double height;
} draw_scene_t;

typedef struct
{
    double scale;
    double offset_x;
    double offset_y;
} scale_data_t;

typedef struct
{
    double min_x;
    double max_x;
    double min_y;
    double max_y;
} view_box_t;

status_t draw_solution_all_points(const points_t &points, const quadrilateral_t &quad, draw_scene_t &draw_scene);
status_t draw_scaled_solution(const points_t &points, const quadrilateral_t &result_points, draw_scene_t &draw_scene);

#endif