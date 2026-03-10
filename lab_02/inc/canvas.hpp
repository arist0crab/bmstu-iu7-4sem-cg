#ifndef __CANVAS_HPP__
#define __CANVAS_HPP__

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include "student_deepseekov.hpp"

class Canvas : public QWidget
{
    Q_OBJECT

    public:
        Canvas(QWidget* parent = nullptr) : QWidget(parent), student_deepseekov(300, 300) 
        {
            // TODO в конструктор студента передавать не захардкоженные координаты, а реальные
        };

    protected:
        void paintEvent(QPaintEvent* event) override
        {
            QPainter painter(this);
            set_up_canvas(painter);
            student_deepseekov.draw(painter);
        }

    public slots:
        status_t move(const double dx, const double dy)
        {
            return student_deepseekov.move(dx, dy);
        }

        status_t rotate(const double angle)
        {
            student_deepseekov.rotate(angle);
            update();

            return SUCCESS_CODE;
        }

    private:
        StudentDeepseekov student_deepseekov;

        status_t set_up_canvas(QPainter &painter)
        {
            QPainterPath path;
            path.addRoundedRect(rect(), 20, 20);
            painter.fillPath(path, Qt::white);

            painter.setRenderHint(QPainter::Antialiasing);
            painter.translate(0, height());
            painter.scale(1, -1);
            painter.setClipRect(rect());

            return SUCCESS_CODE;
        }
};

#endif