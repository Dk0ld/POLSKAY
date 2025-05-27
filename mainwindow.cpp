#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QtMath>
#include <cmath>
#include <QString>
#include <math.h>
#include <paths.h>
#include <QPainterPath>
#include <QLineEdit>
#include "poland.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    button = new QPushButton(this);
    f = new QLineEdit(this);
    xa = new QLineEdit(this);
    xi = new QLineEdit(this);
    button->setGeometry(width() - 10 - 100, 10, 100, 30);
    connect(button, SIGNAL(clicked()), this, SLOT(myClick()));
    f->setGeometry(10, 10, width() - 200, 30);
    xa->setGeometry(width() - 10 - 100, 80, 100, 30);
    xi->setGeometry(width() - 10 - 100, 120, 100, 30);

}

void MainWindow::myClick(){
    ui->label->setGeometry(10, 50, width() - 3*10 - 100, height());
    QPixmap pm(width() - 3*10 - 100, height());
    QPainter painter;
    QPainterPath p0, p1;
    QString xq = xa->text(), yq = xi->text();
    painter.begin(&pm);
    pm.fill(0xAA9900);
    ui->label->setPixmap(pm);
    double pi = qAcos(-1);
    double x, xmax, xmin;
    xmin = xq.toDouble()*(-1);
    xmax = yq.toDouble();
    double y, ymax, ymin;
    ymax = 10;
    ymin = -10;
    int xg, xgmin, xgmax;
    xgmin = 0;
    xgmax = pm.width();
    int yg, ygmin, ygmax;
    ygmin = 0;
    ygmax = pm.height();

    double kx, ky;
    kx = (xgmax - xgmin) / (xmax - xmin);
    ky = (ygmin - ygmax) / (ymax - ymin);

    double x0, y0;
    x0 = xgmin - kx * xmin;
    y0 = ygmin - ky * ymax;

    double step = (xmax - xmin) / (xgmax - xgmin);

    p0.moveTo(0, pm.height() / 2);
    p0.lineTo(pm.width(), pm.height() / 2);
    p1.moveTo(pm.width() / 2, 0);
    p1.lineTo(pm.width() / 2, pm.height());
    QPen pen;
    QString z = f->text();
    QString p = z;
    QPainterPath path;
    x = xmin;
    QString st = "(" + QString::fromStdString(to_string(x)) + ")";
    p.replace("x", st);
    calc(p.toStdString(), y);
    xg = (x0 + kx * x);
    yg = (y0 + ky * y);
    path.moveTo(xg, yg);
    while(x <= xmax){
        st = "(" + QString::fromStdString(to_string(x)) + ")";
        p = z;
        p.replace("x", st);
        calc(p.toStdString(), y);
        if(ky * y <= ygmax && y0 + ky *  y >= ygmin){

            xg = (x0 + kx * x);
            yg = (y0 + ky * y);
            path.lineTo(xg, yg);
            x += step;
        }
        else{

            x += step;
            st = "(" + QString::fromStdString(to_string(x)) + ")";
            p = z;
            p.replace("x", st);
            calc(p.toStdString(), y);
            xg = (x0 + kx * x);
            yg = (y0 + ky * y);
            path.moveTo(xg, yg);

        }
    }
    painter.drawPath(p1);
    painter.drawPath(p0);
    pen.setColor(0x881989);
    painter.setPen(pen);
    painter.drawPath(path);
    ui->label->setPixmap(pm);
}
MainWindow::~MainWindow()
{
    delete ui;
}
