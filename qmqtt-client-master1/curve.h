#ifndef CURVE_H
#define CURVE_H

#include <QWidget>
#include<QSqlQueryModel>
#include<QTableView>
#include<QDebug>
#include<QVector>
#include <QSqlQuery>
#include "qcustomplot.h"

namespace Ui {
class Curve;
}

class Curve : public QWidget
{
    Q_OBJECT

public:
    explicit Curve(QWidget *parent = 0);
    ~Curve();
    void Graph_Show(QCustomPlot *customPlot);

public slots:
    void Graph_Show();

private:
    Ui::Curve *ui;
    QSqlDatabase db1;
};

#endif // CURVE_H
