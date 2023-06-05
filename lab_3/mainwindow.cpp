#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QBrush brush(Qt::red);
    for(int i = 0; i < MainWindow::height(); i += grid_size)
        for(int j = 0; j < MainWindow::width(); j += grid_size)
            painter.drawRect(QRect(j, i, grid_size, grid_size));

    if(!coords_of_ant.isNull()){
        brush.setColor(Qt::red);
        painter.setBrush(brush);
        painter.drawEllipse(coords_of_ant, 5, 5);
    }
    if(!coords_of_fly.isNull()){
        brush.setColor(Qt::blue);
        painter.setBrush(brush);
        painter.drawEllipse(coords_of_fly, 5, 5);
    }
    if(!coords_of_tree.isNull()){
        brush.setColor(Qt::green);
        painter.setBrush(brush);
        painter.drawEllipse(coords_of_tree, tree_radius, tree_radius);
    }

    if(!coords_of_ant.isNull() && !coords_of_fly.isNull() && !coords_of_tree.isNull()){
        painter.setPen(QPen(Qt::yellow, 2));
        for(int i = 0; i < distance.size()-1; i++){
            painter.drawLine(distance[i], distance[i+1]);
        }
    }
}

QPoint PoseOfPoint(QPoint position, int grid_size){
    int countX = 0;
    int countY = 0;
    while(position.x() > grid_size){
        position -= QPoint(grid_size, 0);
        countX++;
    }
    while(position.y() > grid_size){
        position -= QPoint(0, grid_size);
        countY++;
    }
    if(position.x() >= grid_size/2) position.setX(grid_size);
    else position.setX(0);
    if(position.y() >= grid_size/2) position.setY(grid_size);
    else position.setY(0);

    position += QPoint(grid_size*countX, grid_size*countY);
    return position;
}


QVector <QPoint> QPointVector(QPoint start, QPoint finish, QPoint tree, int tree_radius, int grid_size){
    QVector <QPoint> distance;
    distance.append(start);
    if(!start.isNull() && !finish.isNull() && !tree.isNull()){
        for(int i = 0; start != finish; i++){
            if(start.x() > finish.x()){
//                if(((distance[i].x() - grid_size) < (tree.x() + tree_radius)) &&
//                   ((distance[i].y() + grid_size) > (tree.y() - tree_radius)))
//                    start += QPoint(0, grid_size);
//                if(((distance[i].x() - grid_size) < (tree.x() + tree_radius)) &&
//                   ((distance[i].y() - grid_size) < (tree.y() + tree_radius)))
//                    start -= QPoint(0, grid_size);
//                else
                    start -= QPoint(grid_size, 0);
                distance.append(start);
            }
            if(start.x() < finish.x()){
//                if(((distance[i].x() + grid_size) > (tree.x() - tree_radius)) &&
//                   ((distance[i].y() + grid_size) > (tree.y() - tree_radius)))
//                    start -= QPoint(0, grid_size);
//                if(((distance[i].x() + grid_size) > (tree.x() - tree_radius)) &&
//                   ((distance[i].y() - grid_size) < (tree.y() + tree_radius)))
//                    start += QPoint(0, grid_size);
//                else
                    start += QPoint(grid_size, 0);
                distance.append(start);
            }
            if(start.y() > finish.y()){
//                if(((distance[i].x() - grid_size) < (tree.x() + tree_radius)) &&
//                   ((distance[i].y() - grid_size) < (tree.y() + tree_radius)))
//                    start += QPoint(grid_size, 0);
//                if(((distance[i].x() + grid_size) > (tree.x() - tree_radius)) &&
//                   ((distance[i].y() - grid_size) < (tree.y() + tree_radius)))
//                    start -= QPoint(grid_size, 0);
//                else
                    start -= QPoint(0, grid_size);
                distance.append(start);
            }
            if(start.y() < finish.y()){
//                if(((distance[i].x() + grid_size) > (tree.x() - tree_radius)) &&
//                   ((distance[i].y() + grid_size) > (tree.y() - tree_radius)))
//                    start -= QPoint(grid_size, 0);
//                if(((distance[i].x() - grid_size) < (tree.x() + tree_radius)) &&
//                   ((distance[i].y() + grid_size) > (tree.y() - tree_radius)))
//                    start += QPoint(grid_size, 0);
//                else
                    start += QPoint(0, grid_size);
                distance.append(start);
            }
        }
    }
    return distance;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->modifiers() & Qt::ControlModifier)
        coords_of_tree = event->pos();
    else if(event->button() & Qt::LeftButton)
        coords_of_ant = PoseOfPoint(event->pos(), grid_size);
    else if(event->button() & Qt::RightButton)
        coords_of_fly = PoseOfPoint(event->pos(), grid_size);

    distance = QPointVector(coords_of_ant, coords_of_fly, coords_of_tree, tree_radius, grid_size);
    repaint();
}
