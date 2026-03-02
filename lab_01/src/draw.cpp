#include "draw.hpp"

static status_t draw_solution(const quadrilateral_t &quad, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor solution_color);
static status_t draw_line(const point_t &point_1, const point_t &point_2, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor line_color);
static status_t draw_points(draw_scene_t &draw_scene, const points_t &points, const json_t &json_data, const scale_data_t &scale_data, const QColor points_color);
static status_t draw_point_complete(draw_scene_t &draw_scene, const point_t &point, const size_t point_id, const scale_data_t &scale_data, const QColor point_color);
static status_t draw_point(draw_scene_t &draw_scene, const double px, const double py, const QColor point_color);
static status_t draw_point_label(draw_scene_t &draw_scene, const point_t &point, const size_t point_id, const double px, const double py, const QColor &color);

/* находит прямоугольник, в который влезают все переданные точки */
static status_t find_view_box(const points_t &points, view_box_t &box);
static status_t calculate_scale(const view_box_t &box, draw_scene_t &draw_scene, scale_data_t &scale_data);


status_t draw_scaled_solution(draw_scene_t &draw_scene, const points_t &points, const json_t &json_data, const quadrilateral_t &quad)
{
    points_t result_points;
    view_box_t solution_view_box;
    scale_data_t scale_data = { 1, 0, 0 };

    if (draw_scene.scene == nullptr) return ERR_EMPTY_SCENE;
    if (points.size() < 4) return ERR_EMPTY_POINTS;

    result_points = { quad.p1, quad.p2, quad.p3, quad.p4 };

    find_view_box(result_points, solution_view_box);
    calculate_scale(solution_view_box, draw_scene, scale_data);

    draw_scene_reset(draw_scene);
    draw_points(draw_scene, points, json_data, scale_data, ORDINARY_COLOR);
    draw_solution(quad, draw_scene, scale_data, SOLUTION_COLOR);

    return SUCCESS_CODE;
}

status_t draw_solution_all_points(draw_scene_t &draw_scene, const points_t &points, const json_t &json_data, const quadrilateral_t &quad)
{
    points_t result_points;
    view_box_t all_points_view_box;
    scale_data_t scale_data = { 1, 0, 0 };

    if (draw_scene.scene == nullptr) return ERR_EMPTY_SCENE;
    if (points.empty()) return ERR_EMPTY_POINTS;

    if (points.size() < 4)
        draw_points(draw_scene, points, json_data, scale_data, ORDINARY_COLOR);
    else
    {
        find_view_box(points, all_points_view_box);
        calculate_scale(all_points_view_box, draw_scene, scale_data);

        draw_scene_reset(draw_scene);
        draw_points(draw_scene, points, json_data, scale_data, ORDINARY_COLOR);
        draw_solution(quad, draw_scene, scale_data, SOLUTION_COLOR);
    }

    return SUCCESS_CODE;
}

static status_t draw_solution(const quadrilateral_t &quad, draw_scene_t &draw_scene, const scale_data_t &scale_data, const QColor solution_color)
{
    draw_point_complete(draw_scene, quad.p1, quad.i1, scale_data, solution_color);
    draw_point_complete(draw_scene, quad.p2, quad.i2, scale_data, solution_color);
    draw_point_complete(draw_scene, quad.p3, quad.i3, scale_data, solution_color);
    draw_point_complete(draw_scene, quad.p4, quad.i4, scale_data, solution_color);

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

static status_t draw_points(draw_scene_t &draw_scene, const points_t &points, const json_t &json_data, const scale_data_t &scale_data, const QColor points_color)
{
    for (size_t i = 0; i < points.size(); i++)
        draw_point_complete(draw_scene, points[i], json_data[i]["id"], scale_data, points_color);

    return SUCCESS_CODE;
}

static status_t draw_point_complete(draw_scene_t &draw_scene, const point_t &point, const size_t point_id, const scale_data_t &scale_data, const QColor point_color)
{
    double px = point.x() * scale_data.scale + scale_data.offset_x;
    double py = point.y() * scale_data.scale + scale_data.offset_y;

    draw_point(draw_scene, px, py, point_color);
    draw_point_label(draw_scene, point, point_id, px, py, point_color);

    return SUCCESS_CODE;
}

static status_t draw_point(draw_scene_t &draw_scene, const double px, const double py, const QColor point_color)
{
    draw_scene.scene->addEllipse(px - POINT_RADIUS, py - POINT_RADIUS, POINT_RADIUS * 2, POINT_RADIUS * 2, QPen(point_color), QBrush(point_color));
    return SUCCESS_CODE;
}

static status_t draw_point_label(draw_scene_t &draw_scene, const point_t &point, const size_t point_id, const double px, const double py, const QColor &color)
{
    QString labelText = QString("%1: (%2, %3)") .arg(point_id) .arg(point.x(), 0, 'f', 2) .arg(point.y(), 0, 'f', 2);
    
    QGraphicsTextItem *label = draw_scene.scene->addText(labelText);
    label->setDefaultTextColor(color);
    label->setFont(QFont("Arial", 8));
    
    QRectF textRect = label->boundingRect();
    label->setPos(px + POINT_RADIUS + 5, py - textRect.height() / 2);
    
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

status_t draw_scene_reset(draw_scene_t &draw_scene)
{
    status_t sc = SUCCESS_CODE;
    
    if (draw_scene.scene == nullptr)
        sc = ERR_EMPTY_SCENE;

    if (sc == SUCCESS_CODE)
        draw_scene.scene->clear();

    return SUCCESS_CODE;
}