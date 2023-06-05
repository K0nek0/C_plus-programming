#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <math.h>

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

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush brush(Qt::green);
    painter.setBrush(brush);
    painter.drawRect(0, 0, MainWindow::width(), MainWindow::height());

    brush.setColor(Qt::blue);
    painter.setBrush(brush);
    painter.drawRect(pool);

    brush.setColor(Qt::red);
    painter.setBrush(brush);

    for(int i=0; i<flower_circle.length(); i++)
        painter.drawEllipse(flower_circle[i].center, flower_radius, flower_radius);

    for(int i=0; i<flower_square.length(); i++)
        painter.drawRect(flower_square[i]);
}
bool contains(Circle c, QPoint p){
    QPoint dp = c.center - p;
    return (QPoint::dotProduct(dp, dp) <= c.radius*c.radius);
}

bool test(QRect rect, Circle test){
    int c = 0;
    if(contains(test, rect.topLeft())) c++;
    if(contains(test, rect.topRight())) c++;
    if(contains(test, rect.bottomLeft())) c++;
    if(contains(test, rect.bottomRight())) c++;
    if(c == 4) return true;
    if(c != 0) return false;
    return !rect.marginsAdded(QMargins(test.radius, test.radius, test.radius, test.radius)).contains(test.center);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if((pool.contains(event->pos())))
        return;

    if(event->button() & Qt::LeftButton){
        for(int i=0; i<flower_circle.length(); i++){
            QPoint difference = event->pos() - flower_circle[i].center;
            double length = sqrt(difference.x()*difference.x() + difference.y()*difference.y());

            if(length <= flower_radius*2)
                return;
        }
        for(int i=0; i<flower_square.length(); i++)
            if(!test(flower_square[i], {event->pos(), flower_radius})) return;

        flower_circle.append({event->pos(), flower_radius});
    } else {
        QRect flower(0, 0, flower_radius, flower_radius);
        flower.moveCenter(event->pos());
        for(int i=0; i<flower_square.length(); i++)
            if(flower_square[i].intersects(flower)) return;

        for(int i=0; i<flower_circle.length(); i++)
            if(!test(flower, flower_circle[i])) return;
        flower_square.append(flower);
    }
    repaint();
}

//            QPoint difference = event->pos() - flower_square[i].center();
//            double length = sqrt(difference.x()*difference.x() + difference.y()*difference.y());

//            if(length <= flower_radius*2)
//                return;
// -----------------------------------------------------
//            QPoint difference = flower.center() - flower_circle[i];
//            double length = sqrt(difference.x()*difference.x() + difference.y()*difference.y());

//            if(length <= flower_radius*2)
//                return;
