#include "student_deepseekov.hpp"


// конструктор и деструктор
StudentDeepseekov::StudentDeepseekov()
{
    build_body();
    // build_eye();
    // build_eyebrow();
    // build_eyebrow();
}

StudentDeepseekov::~StudentDeepseekov() {};


status_t StudentDeepseekov::draw(QPainter &painter)
{
    return this->body.draw(painter);
}


void StudentDeepseekov::build_body()
{
    this->body.set_color(this->DEEPSEEKOV_SKIN);

    // пузо
    this->body.add_arc(76.7, 72.7, 134, 134, 143, 79, 11, 86);
    this->body.add_arc(58.7, 76, 97, 97, 11, 86, 72, 122);

    // нижний плавник
    this->body.add_bezier_four_points(118, 20, 123, 14.5, 162, 20, 128, 30);

    // хвост и спина
    this->body.add_polyline(std::vector<QPointF>{ QPointF(143, 79), QPointF(146, 88.5), QPointF(155, 91) });
    this->body.add_arc(152.5, 101.5, 22, 22, 163.5, 99.5, 155, 91);
    this->body.add_polyline(std::vector<QPointF>{ QPointF(163.5, 99.5), QPointF(172, 120), QPointF(166, 119) });
    this->body.add_arc(155.5, 123.5, 23, 23, 166, 119, 154, 112.5);
    this->body.add_arc(152.5, 101.5, 22, 22, 141, 103.5, 154, 112.5);
    this->body.add_arc(130, 107, 22, 22, 134, 118, 141, 103.5);
    this->body.add_arc(133.5, 127, 17, 17, 134, 118, 125, 128);
    this->body.add_polyline(std::vector<QPointF>{ QPointF(125.5, 128), QPointF(122, 131), QPointF(119.5, 109.5) });
    this->body.add_arc(130, 107, 22, 22, 123.5, 98, 119.5, 109.5);
    this->body.add_polyline(std::vector<QPointF>{ QPointF(123.5, 98), QPointF(131, 92), QPointF(129, 82.5), QPointF(93, 111.5) });

    // верхний плавник
    this->body.add_arc(99.5, 116, 18, 18, 93, 111.5, 99, 124.5);
    this->body.add_bezier_four_points(99, 124.5, 92, 130.5, 81.5, 122, 72, 122);
}