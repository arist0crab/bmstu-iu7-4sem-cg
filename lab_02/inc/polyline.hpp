// #ifndef __POLYLINE_HPP__
// #define __POLYLINE_HPP__

// #include "status.hpp"
// #include "shape.hpp"
// #include <vector>

// class Polyline : public Shape
// {
//     public:
//         Polyline(const std::vector<QPointF> &points) : Shape(0, 0), points(points) {}

//         status_t draw() const override
//         {
//             // TODO
//             return SUCCESS_CODE;
//         }

//         status_t rotate(const double angle) override
//         {
//             return SUCCESS_CODE;
//         }

//         status_t move(const double dx, const double dy) override
//         {
//             // TODO
//             return SUCCESS_CODE;
//         }

//         status_t scale(const double kx, const double ky) override
//         {
//             // TODO
//             return SUCCESS_CODE;
//         }

//     private:
//         std::vector<QPointF> points;
// };

// #endif