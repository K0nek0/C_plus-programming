#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>

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
    QBrush brush(QColor(0, 255, 155, 155));
    if(count > 1){
        QLineF center(p1, p2);
        painter.drawLine(center);
        v = p2 - p1;
        n1 = QPoint(-v.y(), v.x());
        n2 = QPoint(v.y(), -v.x());

//        painter.drawLine(p2, p2 + n1);
//        painter.drawLine(p2, p2 + n2);
        QLineF l(p2, p1);
        QLineF z(p2, p1);

        l.setAngle(center.angle() + 15);
        z.setAngle(center.angle() - 15);
        painter.drawLine(l);
        painter.drawLine(z);

        QPointF t[] = {QPointF(100, 100), QPointF(150, 150), QPointF(90, 150)};
        painter.setBrush(brush);
        painter.drawPolygon(t, 3);

    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    count++;
    if(count == 1)
        p1 = event->pos();
    if(count == 2)
        p2 = event->pos();
    if(count > 2){
        int c = classify(QLine(n1+p2, n2+p2), event->pos());
        int b = classify(QLine(n1+p1, n2+p1), event->pos());
        if(c != b)
            qDebug("SIDE");
        else
            qDebug("%s", c == BACK ? "BACK": c == FRONT ? "FRONT": "UNDEFINED");
    }
    repaint();
}

int MainWindow::classify(QLine line, QPoint point)
{
    QPoint p0 = line.p1();
    QPoint p1 = line.p2();
    QPoint a = p1 - p0;
    QPoint b = point - p0;
    double aa = a.x()*b.y() - b.x()*a.y();
    if(aa < 0.0)
        return BACK;
    if(aa > 0.0)
        return FRONT;
    return UNDEFINED;
}
