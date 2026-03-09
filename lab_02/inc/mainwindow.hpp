#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include "status.hpp"
#include "canvas.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow 
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        Canvas *canvas;

    private slots:
        status_t on_ButtonRotate_clicked();
};

#endif