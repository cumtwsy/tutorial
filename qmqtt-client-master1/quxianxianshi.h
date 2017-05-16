#ifndef QUXIANXIANSHI_H
#define QUXIANXIANSHI_H
#include<QSqlQueryModel>
#include<QTableView>
#include<QDebug>
#include<QVector>
#include <QSqlQuery>
#include "qcustomplot.h"

#include <QWidget>

namespace Ui {
class QuXianxianshi;
}

class QuXianxianshi : public QWidget
{
    Q_OBJECT

public:
    explicit QuXianxianshi(QWidget *parent = 0);
    ~QuXianxianshi();
    void Graph_Show(QCustomPlot *customPlot);
    void Graph_Show1(QCustomPlot *customPlot);
    void Graph_Show2(QCustomPlot *customPlot);
    void Graph_Show3(QCustomPlot *customPlot);
    void mousePressEvent(QMouseEvent *);
    void slot_mouseRelese(QMouseEvent *event);

private slots:
    void Graph_Show();
    void Graph_Show1();
    void Graph_Show2();
    void Graph_Show3();

private:
    Ui::QuXianxianshi *ui;

};

#endif // QUXIANXIANSHI_H
