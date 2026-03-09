#include "mainwindow.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) 
{
    ui->setupUi(this);
    canvas = ui->canvas;
}

MainWindow::~MainWindow() { delete ui; }

status_t MainWindow::on_ButtonRotate_clicked()
{
    double rotation_angle = ui->RotationInput->value();
    canvas->rotate(rotation_angle);

    return SUCCESS_CODE;
}