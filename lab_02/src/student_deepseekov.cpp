#include "student_deepseekov.hpp"


// конструктор и деструктор
StudentDeepseekov::StudentDeepseekov()
{
    build_lower_fin();
    build_higher_fin();
    build_tail();
    build_body();

    build_belly();
    build_eye();
    build_eyebrow();
}

StudentDeepseekov::~StudentDeepseekov() {};


status_t StudentDeepseekov::draw(QPainter &painter)
{
    this->lower_fin.draw(painter);
    this->higher_fin.draw(painter);
    this->body.draw(painter);
    this->tail.draw(painter);
    this->belly.draw(painter);
    this->eyebrow.draw(painter);
    this->eye.draw(painter);

    return SUCCESS_CODE;
}


void StudentDeepseekov::build_belly()
{
    this->belly.set_color(DEEPSEEKOV_SPOT);
    this->belly.add_bezier_four_points(98, 17.5, 79, 28.5, 69.5, 40.5);
    this->belly.add_arc(67, 38, 8, 8, 69.5, 40.5, 64, 35, false);
    this->belly.add_arc(60.5, 31, 12, 12, 64, 35, 58, 26.5);
    this->belly.add_bezier_four_points(27, 44.5, 22, 54.5, 23, 85);
    this->belly.add_bezier_four_points(85, 95, 80.5, 23.5, 108, 23);
}


void StudentDeepseekov::build_eyebrow()
{
    this->eyebrow.set_color(DEEPSEEKOV_SPOT);
    this->eyebrow.add_arc(97, 71.5, 12, 12, 94, 76, 102.5, 71);
    this->eyebrow.add_bezier_three_points(101, 56.5, 119, 60);
    this->eyebrow.add_bezier_three_points(116, 72.5, 103.5, 81);
    this->eyebrow.add_arc(100, 76, 13, 13, 103.5, 81, 94, 76, false);
}

void StudentDeepseekov::build_eye()
{
    this->eye.set_color(DEEPSEEKOV_SPOT);
    this->eye.add_ellipse(97, 71.5, 1.5, 1.5, 0);
}


void StudentDeepseekov::build_lower_fin()
{
    this->lower_fin.set_color(DEEPSEEKOV_SKIN);
    this->lower_fin.add_bezier_four_points(123, 14.5, 162, 20, 128, 30);
}


void StudentDeepseekov::build_higher_fin()
{
    this->higher_fin.set_color(DEEPSEEKOV_SKIN);
    this->higher_fin.add_arc(99.5, 116, 18, 18, 93, 111.5, 99, 124.5);
    this->higher_fin.add_bezier_four_points(92, 130.5, 81.5, 122, 72, 122);
}


void StudentDeepseekov::build_body()
{
    this->body.set_color(this->DEEPSEEKOV_SKIN);
    this->body.add_arc(76.7, 72.7, 134, 134, 143, 79, 11, 86);
    this->body.add_arc(58.7, 76, 97, 97, 11, 86, 72, 122);
    this->body.add_polyline(std::vector<QPointF>{ QPointF(72, 122), QPointF(93, 111.5), QPointF(129, 82.5), QPointF(143, 79) });
}


void StudentDeepseekov::build_tail()
{
    this->tail.set_color(this->DEEPSEEKOV_SKIN);
    this->tail.add_polyline(std::vector<QPointF>{ QPointF(129, 82.5), QPointF(131, 92), QPointF(123.5, 98) });
    this->tail.add_arc(130, 107, 22, 22, 123.5, 98, 119.5, 109.5);
    this->tail.add_polyline(std::vector<QPointF>{ QPointF(119.5, 109.5), QPointF(122, 131), QPointF(125.5, 128) });
    
    this->tail.add_arc(133.5, 127, 17, 17, 125.5, 128, 134, 118, false);
    
    this->tail.add_arc(130, 107, 22, 22, 134, 118, 141, 103.5);
    this->tail.add_arc(152.5, 101.5, 22, 22, 141, 103.5, 154, 112.5);
    
    this->tail.add_arc(155.5, 123.5, 23, 23, 154, 112.5, 166, 119, false);

    this->tail.add_polyline(std::vector<QPointF>{ QPointF(166, 119), QPointF(172, 120), QPointF(163.5, 99.5) });
    this->tail.add_arc(152.5, 101.5, 22, 22, 163.5, 99.5, 155, 91);
    this->tail.add_polyline(std::vector<QPointF>{ QPointF(155, 91), QPointF(146, 88.5), QPointF(143, 79) });
}
