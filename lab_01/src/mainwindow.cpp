#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "mainwindow.hpp"
#include "ui_mainwindow.h"  

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->pointsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");
}

MainWindow::~MainWindow()
{
    delete ui;
}

status_t MainWindow::find_solution()
{
    status_t sc = SUCCESS_CODE;
    request_t request;

    request.type = FIND_SOLUTION;

    sc = manager(request);

    return sc;
}

status_t MainWindow::draw_scaled_solution()
{
    status_t sc = SUCCESS_CODE;
    request_t request;
    QGraphicsScene *scene;
    double scene_width, scene_height;

    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    scene = ui->graphicsView->scene();
    scene_width = ui->graphicsView->scene()->width();
    scene_height = ui->graphicsView->scene()->height();

    request.type = DRAW_SCALED_SOLUTION;
    request.scene = { scene, scene_width, scene_height };

    sc = manager(request);

    return sc;
}

status_t MainWindow::draw_solution_all_points()
{
    status_t sc = SUCCESS_CODE;
    request_t request;
    QGraphicsScene *scene;
    double scene_width, scene_height;

    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    scene = ui->graphicsView->scene();
    scene_width = ui->graphicsView->scene()->width();
    scene_height = ui->graphicsView->scene()->height();

    request.type = DRAW_SOLUTION_ALL_POINTS;
    request.scene = { scene, scene_width, scene_height };

    sc = manager(request);

    return sc;
}

status_t MainWindow::on_ButtonShowAllPoints_clicked()
{
    draw_solution_all_points();

    return SUCCESS_CODE;
}

status_t MainWindow::on_ButtonShowOnlySolution_clicked()
{
    draw_scaled_solution();

    return SUCCESS_CODE;
}

status_t MainWindow::on_ButtonLoadJson_clicked()
{
    status_t sc = SUCCESS_CODE;
    request_t request;

    QString path = QFileDialog::getOpenFileName(this, "Выбор файла", "", "Json files (*.json)");

    request.type = JSON_LOAD;
    request.filename = path.toUtf8().data();;

    sc = manager(request);
    if (sc == SUCCESS_CODE) sc = find_solution();
    if (sc == SUCCESS_CODE) draw_scaled_solution();

    return sc;
}
