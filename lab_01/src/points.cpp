#include "points.hpp"

static status_t check_point_coordinates_uniq(const points_t &points, const point_t &new_point);
static status_t ensure_point_exists(const json_t &json_data, const size_t point_id);
static status_t ensure_point_id_free(const json_t &json_data, const size_t point_id);
static status_t delete_point_on_index_from_points(points_t &points, const size_t delete_point_index);
static status_t two_points_are_different(const point_t &point_1, const point_t &point_2);
static status_t find_point_index_from_id(ssize_t &point_index, const json_t &json_data, const size_t changed_point_id);

status_t delete_point_from_points(points_t &points, json_t &json_data, const size_t delete_point_id)
{
    status_t sc = SUCCESS_CODE;
    ssize_t point_index = -1;

    sc = find_point_index_from_id(point_index, json_data, delete_point_id);
    if (sc == SUCCESS_CODE)
        delete_point_on_index_from_points(points, point_index);

    return sc;
}

status_t add_point_to_points(points_t &points, const point_t &new_point)
{
    points.push_back(new_point);

    return SUCCESS_CODE;
}

status_t read_points_from_json(const json_t &json, points_t &points)
{
    point_t point;

    points.clear();

    for (const auto &item : json)
    {
        point.setX(item["x"]);
        point.setY(item["y"]);
        points.push_back(point);
    }

    return SUCCESS_CODE;
}

status_t change_point_in_points(points_t &points, json_t &json_data, const size_t changed_point_id, const point_t &changed_point)
{
    status_t sc = SUCCESS_CODE;
    ssize_t point_index = -1;
    const double new_x = changed_point.x();
    const double new_y = changed_point.y();

    sc = find_point_index_from_id(point_index, json_data, changed_point_id);
    if (sc == SUCCESS_CODE)
    {
        points[point_index].setX(new_x);
        points[point_index].setY(new_y);
    }

    return sc;
}

status_t check_point_can_be_deleted(const json_t &json_data, const size_t point_id)
{
    return ensure_point_exists(json_data, point_id);
}

status_t check_point_can_be_changed(const json_t &json_data, const points_t &points, const point_t &changed_point, const size_t changed_point_id)
{
    status_t sc = SUCCESS_CODE;

    sc = ensure_point_exists(json_data, changed_point_id);
    if (sc == SUCCESS_CODE)
        sc = check_point_coordinates_uniq(points, changed_point);

    return sc;
}

status_t check_new_point_can_be_added(const json_t &json_data, const points_t &points, const point_t &new_point, const size_t new_point_id)
{
    status_t sc = SUCCESS_CODE;

    sc = ensure_point_id_free(json_data, new_point_id);

    if (sc == SUCCESS_CODE)
        sc = check_point_coordinates_uniq(points, new_point);

    return sc;
}

static status_t delete_point_on_index_from_points(points_t &points, const size_t delete_point_index)
{
    points.erase(points.begin() + delete_point_index);

    return SUCCESS_CODE;
}

static status_t check_point_coordinates_uniq(const points_t &points, const point_t &point)
{
    status_t sc = SUCCESS_CODE;

    for (size_t i = 0; sc == SUCCESS_CODE && i < points.size(); i++)
        sc = two_points_are_different(points[i], point);

    return sc;
}

static status_t ensure_point_id_free(const json_t &json_data, const size_t point_id)
{
    bool new_point_id_free = true;

    for (size_t i = 0; new_point_id_free && i < json_data.size(); i++)
        new_point_id_free = (json_data[i]["id"] != point_id);

    return (new_point_id_free) ? SUCCESS_CODE : ERR_INVALID_POINT;
}

static status_t ensure_point_exists(const json_t &json_data, const size_t point_id)
{
    bool point_exists = false;

    for (size_t i = 0; !point_exists && i < json_data.size(); i++)
        point_exists = (json_data[i]["id"] == point_id);

    return (point_exists) ? SUCCESS_CODE : ERR_POINT_DOESNT_EXIST;
}

static status_t two_points_are_different(const point_t &point_1, const point_t &point_2)
{
    bool x_coordinates_equal = abs(point_1.x() - point_2.x()) < EPS;
    bool y_coordinates_equal = abs(point_1.y() - point_2.y()) < EPS;

    return (x_coordinates_equal && y_coordinates_equal) ? ERR_TWO_POINTS_EQUAL : SUCCESS_CODE; 
}

static status_t find_point_index_from_id(ssize_t &point_index, const json_t &json_data, const size_t changed_point_id)
{
    status_t sc = SUCCESS_CODE;
    point_index = -1;

    for (size_t i = 0; point_index < 0 && i < json_data.size(); i++)
        if (json_data[i]["id"] == changed_point_id)
            point_index = i;

    if (point_index < 0) sc = ERR_POINT_DOESNT_EXIST;

    return sc;
}

status_t points_clear(points_t &points)
{
    points.clear();
    return SUCCESS_CODE;
}