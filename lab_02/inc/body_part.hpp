#ifndef __BODY_PART_HPP__
#define __BODY_PART_HPP__

#include "status.hpp"
#include <QPainterPath>
#include <QPainter>
#include <QPointF>
#include <QPen>
#include <vector>

static const size_t default_pen_width = 2;

typedef enum
{
    FIRST,
    SECOND,
    THIRD,
    FOURTH
} ellipse_quarter_t;

class BodyPart
{
    private:
        QColor color;
        QPainterPath path;

        double calculate_ellipse_point_angle(const double center_x, const double center_y, const double px, const double py);
        ellipse_quarter_t calculate_ellipse_point_quarter(const double center_x, const double center_y, const double px, const double py);

    public:
        BodyPart(const double init_x, const double init_y);
        ~BodyPart();

        void set_color(QColor new_color);
        void add_arc(const double center_x, const double center_y, const double width, const double height, const double p1_x, const double p1_y, const double p2_x, const double p2_y, bool clockwise = true);
        void add_bezier_four_points(const double p1_x, const double p1_y, const double p2_x, const double p2_y, const double p3_x, const double p3_y, const double p4_x, const double p4_y);
        void add_polyline(const std::vector<QPointF> &points);
        void unit_body_part_pathes(BodyPart &body_part);

        status_t draw(QPainter &painter) const;
        bool bodypart_contains_no_points() const;
};


#endif