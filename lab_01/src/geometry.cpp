#include "geometry.hpp"

/* основные функции */
static status_t process_quadrilateral(const quadrilateral_t &current_points, quadrilateral_t &result_points, double &min_avg, bool &first_avg_found);

/* вычисление ромбовитости фигуры и другие расчеты */
static status_t calculate_figure_avg(const quadrilateral_t &figure, double &figure_avg);
static status_t calculate_distance(const point_t &p1, const point_t &p2, double &distance);

/* проверка фигуры на валидность */
static status_t check_figure_valid(const quadrilateral_t &figure);
static status_t points_lie_on_one_line(const quadrilateral_t &quadrilateral);
static status_t sides_intersect(const point_t &p1, const point_t &p2, const point_t &p3, const point_t &p4);
static status_t calculate_orientation(const point_t &p1, const point_t &p2, const point_t &p3, double &result_orientation);


status_t find_the_most_rhombus(const json_t &json_data, const points_t &points, quadrilateral_t &result_points)
{
    status_t sc = SUCCESS_CODE;

    double min_avg = 0;
    bool first_avg_found = false;
    quadrilateral_t current_figure;
    const size_t points_quantity = points.size();

    if (points_quantity < 4) return ERR_ARGS;

    for (size_t i = 0; i < points_quantity - 3; i++)
    {
        for (size_t j = i + 1; j < points_quantity - 2; j++)
        {
            for (size_t k = j + 1; k < points_quantity - 1; k++)
            {
                for (size_t l = k + 1; l < points_quantity; l++)
                {
                    current_figure = { points[i], points[j], points[k], points[l], json_data[i]["id"], json_data[j]["id"], json_data[k]["id"], json_data[l]["id"] };
                    process_quadrilateral(current_figure, result_points, min_avg, first_avg_found);
                }
            }
        }
    }

    if (!first_avg_found) sc = ERR_DATA;

    return sc;
}


static status_t process_quadrilateral(const quadrilateral_t &current_points, quadrilateral_t &result_points, double &min_avg, bool &first_avg_found)
{
    double current_avg;

    quadrilaterals_t figure_cycles = {
        { current_points.p1, current_points.p2, current_points.p3, current_points.p4, current_points.i1, current_points.i2, current_points.i3, current_points.i4 },
        { current_points.p1, current_points.p2, current_points.p4, current_points.p3, current_points.i1, current_points.i2, current_points.i4, current_points.i3 },
        { current_points.p1, current_points.p3, current_points.p2, current_points.p4, current_points.i1, current_points.i3, current_points.i2, current_points.i4 }
    };

    for (const auto &figure : figure_cycles)
    {
        if (check_figure_valid(figure) == SUCCESS_CODE)
        {
            calculate_figure_avg(figure, current_avg);
            if (!first_avg_found || current_avg < min_avg)
            {
                min_avg = current_avg;
                result_points = figure;
                first_avg_found = true;
            }
        }
    }

    return SUCCESS_CODE;
}


static status_t calculate_figure_avg(const quadrilateral_t &figure, double &figure_avg)
{
    double sides_sum, sides_avg;
    double side_1, side_2, side_3, side_4;
    double abs_p1, abs_p2, abs_p3, abs_p4;

    calculate_distance(figure.p1, figure.p2, side_1);
    calculate_distance(figure.p2, figure.p3, side_2);
    calculate_distance(figure.p3, figure.p4, side_3);
    calculate_distance(figure.p4, figure.p1, side_4);

    sides_sum = side_1 + side_2 + side_3 + side_4;
    sides_avg = sides_sum / 4;

    abs_p1 = std::abs(sides_avg - side_1);
    abs_p2 = std::abs(sides_avg - side_2);
    abs_p3 = std::abs(sides_avg - side_3);
    abs_p4 = std::abs(sides_avg - side_4);

    figure_avg = abs_p1 + abs_p2 + abs_p3 + abs_p4;

    return SUCCESS_CODE;
}


static status_t calculate_distance(const point_t &p1, const point_t &p2, double &distance)
{
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();

    distance = std::sqrt(dx * dx  + dy * dy);

    return SUCCESS_CODE;
}


static status_t check_figure_valid(const quadrilateral_t &figure)
{
    status_t sc = SUCCESS_CODE;

    sc = points_lie_on_one_line(figure);

    if (sc == SUCCESS_CODE)
        sc = sides_intersect(figure.p1, figure.p2, figure.p3, figure.p4);

    if (sc == SUCCESS_CODE)
        sc = sides_intersect(figure.p2, figure.p3, figure.p4, figure.p1);

    return sc;
}


static status_t sides_intersect(const point_t &p1, const point_t &p2, const point_t &p3, const point_t &p4)
{
    status_t sc = SUCCESS_CODE;
    double o1, o2, o3, o4;

    calculate_orientation(p1, p2, p3, o1);
    calculate_orientation(p1, p2, p4, o2);
    calculate_orientation(p3, p4, p1, o3);
    calculate_orientation(p3, p4, p2, o4);

    if (o1 * o2 < 0 && o3 * o4 < 0)
        sc = ERR_FIGURE;

    return sc;
}


static status_t points_lie_on_one_line(const quadrilateral_t &quadrilateral)
{
    status_t sc = SUCCESS_CODE;
    double triple_points_orientation_1;
    double triple_points_orientation_2;

    calculate_orientation(quadrilateral.p1, quadrilateral.p2, quadrilateral.p3, triple_points_orientation_1);
    calculate_orientation(quadrilateral.p1, quadrilateral.p2, quadrilateral.p4, triple_points_orientation_2);

    if (std::abs(triple_points_orientation_1) < EPS && std::abs(triple_points_orientation_2) < EPS)
        sc = ERR_FIGURE;

    return sc;
}


static status_t calculate_orientation(const point_t &p1, const point_t &p2, const point_t &p3, double &result_orientation)
{
    result_orientation = (p2.x() - p1.x()) * (p3.y() - p1.y()) - (p2.y() - p1.y()) * (p3.x() - p1.x());
    return SUCCESS_CODE;
}

status_t is_quadrilateral_valid(const quadrilateral_t &quad)
{
    return (quad.i1 > 0 && quad.i2 > 0 && quad.i3 > 0 && quad.i4 > 0) ? SUCCESS_CODE : ERR_EMPTY_POINTS;
}