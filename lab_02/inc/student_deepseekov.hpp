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
        BodyPart lower_fin{118, 20};  // нижний плавник
        BodyPart higher_fin{72, 122};  // верхний плавник
        BodyPart tail{129, 82.5};
        // Body eye;  // глаз
        // Body eyebrow;  // роскошная бровь
        BodyPart belly{108, 23}; // пятно на пузе

        void build_body();
        void build_tail();
        void build_lower_fin();
        void build_higher_fin();
        // void build_eye();
        // void build_eyebrow();
        void build_belly();

    public:
        StudentDeepseekov();
        ~StudentDeepseekov();

        status_t draw(QPainter &painter);  
};

#endif