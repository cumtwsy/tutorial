#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QSqlQuery>
#include <QTimer>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QPointF>
#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <QMessageBox>
#include <qtextcodec.h>
#include"qcustomplot.h"
#include"quxianxianshi.h"
#include"curve.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    double num[10];
    int n;

public slots:
    void timerUpdate();
    void timer();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


private:
    Ui::Form *ui;
};

#endif // FORM_H
