#include "mainwindow.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) 
{
    ui->setupUi(this);
    canvas = ui->canvas;
}

MainWindow::~MainWindow() { delete ui; }
