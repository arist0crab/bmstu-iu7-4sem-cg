#include "draw.hpp"

static status_t draw_solution(const quadrilateral_t &quad, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor solution_color);
static status_t draw_line(const point_t &point_1, const point_t &point_2, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor line_color);
static status_t draw_points(const points_t &points, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor points_color);
static status_t draw_point(const point_t &point, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor point_color);
static status_t draw_scene_reset(draw_scene_t &draw_scene);

/* находит прямоугольник, в который влезают все переданные точки */
static status_t find_view_box(const points_t &points, view_box_t &box);
static status_t calculate_scale(const view_box_t &box, draw_scene_t &draw_scene, scale_data_t &scale_data);


status_t draw_scaled_solution(const points_t &points, const quadrilateral_t &quad, draw_scene_t &draw_scene)
{
    points_t result_points;
    scale_data_t scale_data;
    view_box_t solution_view_box;

    if (draw_scene.scene == nullptr) return ERR_EMPTY_SCENE;
    if (points.empty()) return ERR_EMPTY_POINTS;

    result_points = { quad.p1, quad.p2, quad.p3, quad.p4 };

    find_view_box(result_points, solution_view_box);
    calculate_scale(solution_view_box, draw_scene, scale_data);

    draw_scene_reset(draw_scene);
    draw_points(points, draw_scene, scale_data, ORDINARY_COLOR);
    draw_solution(quad, draw_scene, scale_data, SOLUTION_COLOR);

    return SUCCESS_CODE;
}

status_t draw_solution_all_points(const points_t &points, const quadrilateral_t &quad, draw_scene_t &draw_scene)
{
    points_t result_points;
    scale_data_t scale_data;
    view_box_t all_points_view_box;

    if (draw_scene.scene == nullptr) return ERR_EMPTY_SCENE;
    if (points.empty()) return ERR_EMPTY_POINTS;

    find_view_box(points, all_points_view_box);
    calculate_scale(all_points_view_box, draw_scene, scale_data);

    draw_scene_reset(draw_scene);
    draw_points(points, draw_scene, scale_data, ORDINARY_COLOR);
    draw_solution(quad, draw_scene, scale_data, SOLUTION_COLOR);

    return SUCCESS_CODE;
}

static status_t draw_solution(const quadrilateral_t &quad, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor solution_color)
{
    draw_point(quad.p1, draw_scene, scale_data, solution_color);
    draw_point(quad.p2, draw_scene, scale_data, solution_color);
    draw_point(quad.p3, draw_scene, scale_data, solution_color);
    draw_point(quad.p4, draw_scene, scale_data, solution_color);

    draw_line(quad.p1, quad.p2, draw_scene, scale_data, solution_color);
    draw_line(quad.p2, quad.p3, draw_scene, scale_data, solution_color);
    draw_line(quad.p3, quad.p4, draw_scene, scale_data, solution_color);
    draw_line(quad.p4, quad.p1, draw_scene, scale_data, solution_color);

    return SUCCESS_CODE;
}

static status_t draw_line(const point_t &point_1, const point_t &point_2, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor line_color)
{
    double p1_x = point_1.x() * scale_data.scale + scale_data.offset_x;
    double p1_y = point_1.y() * scale_data.scale + scale_data.offset_y;
    double p2_x = point_2.x() * scale_data.scale + scale_data.offset_x;
    double p2_y = point_2.y() * scale_data.scale + scale_data.offset_y;

    draw_scene.scene->addLine(p1_x, p1_y, p2_x, p2_y, QPen(line_color));

    return SUCCESS_CODE;
}

static status_t draw_points(const points_t &points, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor points_color)
{
    for (const auto &current_point : points)
        draw_point(current_point, draw_scene, scale_data, points_color);

    return SUCCESS_CODE;
}

static status_t draw_point(const point_t &point, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor point_color)
{
    double px = point.x() * scale_data.scale + scale_data.offset_x;
    double py = point.y() * scale_data.scale + scale_data.offset_y;

    draw_scene.scene->addEllipse(px - POINT_RADIUS, py - POINT_RADIUS, POINT_RADIUS * 2, POINT_RADIUS * 2, QPen(point_color), QBrush(point_color));
    
    return SUCCESS_CODE;
}

static status_t find_view_box(const points_t &points, view_box_t &box)
{
    status_t sc = SUCCESS_CODE;

    if (points.empty()) sc = ERR_EMPTY_POINTS;

    if (sc == SUCCESS_CODE)
    {
        box.min_x = points[0].x();
        box.max_x = points[0].x();
        box.min_y = points[0].y();
        box.max_y = points[0].y();

        for (const auto &current_point : points)
        {
            box.min_x = std::min(box.min_x, current_point.x());
            box.max_x = std::max(box.max_x, current_point.x());
            box.min_y = std::min(box.min_y, current_point.y());
            box.max_y = std::max(box.max_y, current_point.y());
        }
    }

    return sc;
}

static status_t calculate_scale(const view_box_t &box, draw_scene_t &draw_scene, scale_data_t &scale_data)
{
    double delta_box_x = box.max_x - box.min_x;
    double delta_box_y = box.max_y - box.min_y;
    double scale_x = (draw_scene.width - 2 * SCENE_PADDING) / delta_box_x;
    double scale_y = (draw_scene.height - 2 * SCENE_PADDING) / delta_box_y;
    double result_scale = std::min(scale_x, scale_y);

    double box_center_x = (box.min_x + box.max_x) / 2.0;
    double box_center_y = (box.min_y + box.max_y) / 2.0;
    double scene_center_x = draw_scene.width / 2.0;
    double scene_center_y = draw_scene.height / 2.0;

    scale_data.scale = result_scale;
    scale_data.offset_x = scene_center_x - box_center_x * result_scale;
    scale_data.offset_y = scene_center_y - box_center_y * result_scale;

    return SUCCESS_CODE;
}

static status_t draw_scene_reset(draw_scene_t &draw_scene)
{
    draw_scene.scene->clear();
    return SUCCESS_CODE;
}