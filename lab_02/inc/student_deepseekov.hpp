#ifndef __STUDENT_DEEPSEEKOV_HPP__
#define __STUDENT_DEEPSEEKOV_HPP__

#include "status.hpp"
#include "body_part.hpp"
#include <QPainter>
#include <QPen>
#include <QColor>
#include <vector>

class StudentDeepseekov
{
    private:
        const QColor DEEPSEEKOV_SKIN = QColor(73, 97, 211);
        const QColor DEEPSEEKOV_SPOT = QColor(255, 255, 255);

        // TODO вынести центры в константы
        BodyPart body{76.7, 72.7};  // тело (хвост, пузо, плавники)
        // Body eye;  // глаз
        // Body eyebrow;  // роскошная бровь
        // Body belly; // пятно на пузе

        void build_body();
        // void build_eye();
        // void build_eyebrow();
        // void build_belly();

    public:
        StudentDeepseekov();
        ~StudentDeepseekov();

        status_t draw(QPainter &painter);  
};

#endif