#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "status.hpp"
#include "json.hpp"
#include <QPointF>
#include <vector>
#include <cmath>

#define EPS 1e-9

using point_t = QPointF;
using points_t = std::vector<QPointF>;

typedef struct 
{
    point_t p1;
    point_t p2;
    point_t p3;
    point_t p4;
    size_t i1;
    size_t i2;
    size_t i3;
    size_t i4;
} quadrilateral_t;

using quadrilaterals_t = std::vector<quadrilateral_t>;

status_t read_points_from_json(const json_t &json, points_t &points);
status_t find_the_most_rhombus(const json_t &json_data, const points_t &points, quadrilateral_t &result_points);

#endif