#ifndef __MAIN_GUI_H__
#define __MAIN_GUI_H__

#include "status.hpp"
#include "manager.hpp"
#include <QMainWindow>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        status_t draw_solution_all_points();
        status_t draw_scaled_solution();
        status_t find_solution();


    private:
        Ui::MainWindow *ui; 

    private slots:
        status_t on_ButtonLoadJson_clicked();
        status_t on_ButtonShowAllPoints_clicked();
        status_t on_ButtonShowOnlySolution_clicked();
};

#endif