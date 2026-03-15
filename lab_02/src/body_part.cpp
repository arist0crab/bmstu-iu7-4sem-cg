#include "body_part.hpp"


// конструктор и деструктор
BodyPart::BodyPart(const double init_x, const double init_y) 
{
    this->path.moveTo(init_x, init_y);
};

BodyPart::~BodyPart() {};

status_t BodyPart::draw(QPainter &painter) const
{
    if (bodypart_contains_no_points())
        return ERR_BODYPART_CONTAINS_NO_POINTS;

    QPen pen = QPen(this->color, default_pen_width);
    painter.setPen(pen);
    painter.setBrush(this->color);
    painter.drawPath(this->path);

    return SUCCESS_CODE;
}


bool BodyPart::bodypart_contains_no_points() const
{
    return this->path.isEmpty();
}


void BodyPart::set_color(QColor new_color)
{
    this->color = new_color;
}


double BodyPart::calculate_ellipse_point_angle(const double center_x, const double center_y, const double px, const double py)
{
    const double dx = abs(px - center_x);
    const double dy = abs(py - center_y);

    const ellipse_quarter_t elliipse_point_quarter = calculate_ellipse_point_quarter(center_x, center_y, px, py);

    double result_angle = atan2(dy, dx) * 180 / M_PI;

    switch (elliipse_point_quarter)
    {
        case FIRST:
            result_angle = 360 - result_angle;
            break;

        case SECOND:
            result_angle = result_angle + 180;
            break;

        case THIRD:
            result_angle = 180 - result_angle;
            break;

        case FOURTH:
            break;
    }

    return result_angle;
}


void BodyPart::add_arc(const double center_x, const double center_y, const double width, const double height, const double p1_x, const double p1_y, const double p2_x, const double p2_y, bool clockwise)
{
    double rectangle_left_top_x = center_x - width / 2;
    double rectangle_left_top_y = center_y - height / 2;

    double start_angle = calculate_ellipse_point_angle(center_x, center_y, p1_x, p1_y);
    double end_angle = calculate_ellipse_point_angle(center_x, center_y, p2_x, p2_y);

    if (start_angle > end_angle && clockwise)
        start_angle -= 360;

    const double sweep_angle = end_angle - start_angle;

    this->path.arcTo(rectangle_left_top_x, rectangle_left_top_y, width, height, start_angle, sweep_angle);
}


ellipse_quarter_t BodyPart::calculate_ellipse_point_quarter(const double center_x, const double center_y, const double px, const double py)
{
    if (px > center_x && py <= center_y)
        return FOURTH;

    if (px <= center_x && py < center_y)
        return THIRD;

    if (px < center_x && py >= center_y)
        return SECOND;

    return FIRST;
}

void BodyPart::add_bezier_four_points(const double p2_x, const double p2_y, const double p3_x, const double p3_y, const double p4_x, const double p4_y)
{
    this->path.cubicTo(p2_x, p2_y, p3_x, p3_y, p4_x, p4_y);
}


void BodyPart::add_bezier_three_points(const double p2_x, const double p2_y, const double p3_x, const double p3_y)
{
    this->path.quadTo(p2_x, p2_y, p3_x, p3_y);
}


void BodyPart::add_polyline(const std::vector<QPointF> &points)
{
    if (points.empty())
        return;

    for (size_t i = 0; i < points.size(); i++)
        path.lineTo(points[i]);
}


void BodyPart::add_ellipse(const double center_x, const double center_y, const double radius_x, const double radius_y, const double angle_deg)
{
    const size_t SEGMENTS_QUANTITY = 720;

    const double angle_rad = angle_deg * M_PI / 180.0;
    const double cos_a = cos(angle_rad);
    const double sin_a = sin(angle_rad);
    
    double t = 0.0;
    double x = radius_x * cos(t);
    double y = radius_y * sin(t);
    
    double x_rot = x * cos_a - y * sin_a;
    double y_rot = x * sin_a + y * cos_a;
    
    this->path.moveTo(center_x + x_rot, center_y + y_rot);
    
    for (int i = 1; i <= SEGMENTS_QUANTITY; ++i) {
        double t = 2.0 * M_PI * i / SEGMENTS_QUANTITY;
        
        double x = radius_x * cos(t);
        double y = radius_y * sin(t);
        
        double x_rot = x * cos_a - y * sin_a;
        double y_rot = x * sin_a + y * cos_a;
        
        this->path.lineTo(center_x + x_rot, center_y + y_rot);
    }
    
    this->path.closeSubpath();
}