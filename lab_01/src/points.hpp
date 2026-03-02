#ifndef __POINTS_HPP__
#define __POINTS_HPP__

#include "status.hpp"
#include "json_nlohmann.hpp"
#include <QPointF>
#include <vector>

#define EPS 1e-9

using point_t = QPointF;
using points_t = std::vector<QPointF>;

status_t points_clear(points_t &points);
status_t read_points_from_json(const json_t &json, points_t &points);
status_t add_point_to_points(points_t &points, const point_t &new_point);
status_t delete_point_from_points(points_t &points, json_t &json_data, const size_t delete_point_id);
status_t change_point_in_points(points_t &points, json_t &json_data, const size_t changed_point_id, const point_t &changed_point);

/* проверки возможности изменения точек */
status_t check_point_can_be_deleted(const json_t &json_data, const size_t point_id);
status_t check_new_point_can_be_added(const json_t &json_data, const points_t &points, const point_t &new_point, const size_t new_point_id);
status_t check_point_can_be_changed(const json_t &json_data, const points_t &points, const point_t &changed_point, const size_t changed_point_id);

#endif