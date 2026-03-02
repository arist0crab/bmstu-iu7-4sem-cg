#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "mainwindow.hpp"  

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->pointsTable->verticalHeader()->setVisible(false);
    ui->pointsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ===================================================
//                  public functions
// ===================================================

status_t MainWindow::find_solution()
{
    status_t sc = SUCCESS_CODE;
    request_t request;

    request.type = FIND_SOLUTION;

    sc = manager(request);

    return sc;
}

status_t MainWindow::flush_points_to_table()
{
    status_t sc = SUCCESS_CODE;
    table_widget_t table_widget;
    request_t request;

    table_widget.table = ui->pointsTable;
    table_widget.table_size = ui->pointsTable->rowCount();

    request.type = FLUSH_POINTS_TO_TABLE;
    request.table_widget = table_widget;

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

// ===================================================
//           on button clicked functions
// ===================================================

status_t MainWindow::on_ButtonClearAll_clicked()
{
    status_t sc = SUCCESS_CODE;
    request_t request;
    table_widget_t table_widget;
    QGraphicsScene *scene;
    double scene_width, scene_height;

    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    scene = ui->graphicsView->scene();
    scene_width = ui->graphicsView->scene()->width();
    scene_height = ui->graphicsView->scene()->height();

    table_widget.table = ui->pointsTable;
    table_widget.table_size = ui->pointsTable->rowCount();

    request.type = CLEAR_ALL;
    request.scene = { scene, scene_width, scene_height };
    request.table_widget = table_widget;

    sc = manager(request);
    show_status_message(sc, this);

    return sc;
}

status_t MainWindow::on_ButtonShowAllPoints_clicked()
{
    status_t sc = draw_solution_all_points();
    show_status_message(sc, this);

    return SUCCESS_CODE;
}

status_t MainWindow::on_ButtonSaveResult_clicked()
{
    status_t sc = SUCCESS_CODE;
    request_t request;

    QString path = QFileDialog::getSaveFileName(this, "Сохранить JSON", "points.json","JSON files (*.json);;All files (*)");

    if (path.isEmpty())
        sc = ERR_FILE;

    if (sc == SUCCESS_CODE)
    {
        request.type = SAVE_RESULT;
        request.filename = path.toUtf8().data();
        sc = manager(request);
    }

    show_status_message(sc, this);

    return sc;
}

status_t MainWindow::on_ButtonDeletePoint_clicked()
{
    status_t sc = SUCCESS_CODE;
    request_t request;
    table_widget_t table_widget;
    QGraphicsScene *scene;
    double scene_width, scene_height;

    const size_t delete_point_id = ui->idInputBox->value();
    
    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    scene = ui->graphicsView->scene();
    scene_width = ui->graphicsView->scene()->width();
    scene_height = ui->graphicsView->scene()->height();

    table_widget.table = ui->pointsTable;
    table_widget.table_size = ui->pointsTable->rowCount();

    request.type = DELETE_POINT;
    request.scene = { scene, scene_width, scene_height };
    request.table_widget = table_widget;
    request.point_id = delete_point_id;

    sc = manager(request);
    if (sc == SUCCESS_CODE)
        sc = find_solution();
    if (sc == SUCCESS_CODE)
        sc = draw_scaled_solution();

    show_status_message(sc, this);
    
    return sc;
}

status_t MainWindow::on_ButtonAddPoint_clicked()
{
    status_t sc = SUCCESS_CODE;
    request_t request;
    table_widget_t table_widget;
    QGraphicsScene *scene;
    double scene_width, scene_height;

    const size_t new_point_id = ui->idInputBox->value();
    const double new_point_x = ui->xInputBox->value();
    const double new_point_y = ui->yInputBox->value();

    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    scene = ui->graphicsView->scene();
    scene_width = ui->graphicsView->scene()->width();
    scene_height = ui->graphicsView->scene()->height();

    table_widget.table = ui->pointsTable;
    table_widget.table_size = ui->pointsTable->rowCount();

    request.type = ADD_NEW_POINT;
    request.scene = { scene, scene_width, scene_height };
    request.table_widget = table_widget;
    request.point = QPointF(new_point_x, new_point_y);
    request.point_id = new_point_id;

    sc = manager(request);
    if (sc == SUCCESS_CODE)
        sc = find_solution();
    if (sc == SUCCESS_CODE)
        sc = draw_scaled_solution();

    show_status_message(sc, this);
    
    return sc;
}

status_t MainWindow::on_ButtonChangePoint_clicked()
{
    status_t sc = SUCCESS_CODE;
    request_t request;
    table_widget_t table_widget;
    QGraphicsScene *scene;
    double scene_width, scene_height;

    const size_t changed_point_id = ui->idInputBox->value();
    const double changed_point_x = ui->xInputBox->value();
    const double changed_point_y = ui->yInputBox->value();

    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    scene = ui->graphicsView->scene();
    scene_width = ui->graphicsView->scene()->width();
    scene_height = ui->graphicsView->scene()->height();

    table_widget.table = ui->pointsTable;
    table_widget.table_size = ui->pointsTable->rowCount();

    request.type = CHANGE_POINT;
    request.scene = { scene, scene_width, scene_height };
    request.table_widget = table_widget;
    request.point = QPointF(changed_point_x, changed_point_y);
    request.point_id = changed_point_id;

    sc = manager(request);
    if (sc == SUCCESS_CODE)
        sc = find_solution();
    if (sc == SUCCESS_CODE)
        sc = draw_scaled_solution();

    show_status_message(sc, this);

    return sc;
}

status_t MainWindow::on_ButtonShowOnlySolution_clicked()
{
    status_t sc =  draw_scaled_solution();
    show_status_message(sc, this);

    return SUCCESS_CODE;
}

status_t MainWindow::on_ButtonLoadJson_clicked()
{
    status_t sc = SUCCESS_CODE;
    request_t request;

    QString path = QFileDialog::getOpenFileName(this, "Выбор файла", "", "Json files (*.json)");

    if (path.isEmpty())
        sc = ERR_FILE;

    if (sc == SUCCESS_CODE)
    {
        request.type = JSON_LOAD;
        request.filename = path.toUtf8().data();;

        sc = manager(request);
        if (sc == SUCCESS_CODE) sc = find_solution();
        if (sc == SUCCESS_CODE) draw_scaled_solution();
        if (sc == SUCCESS_CODE) flush_points_to_table();
    }

    show_status_message(sc, this);

    return sc;
}
