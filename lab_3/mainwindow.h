#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    int grid_size = 20;
    int tree_radius = 50;
    QPoint coords_of_ant;
    QPoint coords_of_fly;
    QPoint coords_of_tree;
    QVector <QPoint> distance;
};
#endif // MAINWINDOW_H
