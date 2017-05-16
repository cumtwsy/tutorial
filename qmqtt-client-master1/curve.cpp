#include "curve.h"
#include "ui_curve.h"

Curve::Curve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Curve)
{
    ui->setupUi(this);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    db1 = QSqlDatabase::addDatabase("QMYSQL");
    db1.setHostName("localhost");
    db1.setDatabaseName("penguanji");
    db1.setUserName("root");
    db1.setPassword("12345678");
    if (!db1.open())
        qDebug() << "Failed to connect to root mysql admin";
    else qDebug() << "open";
    Graph_Show(ui->widget);
}

Curve::~Curve()
{
    delete ui;
}

void Curve::Graph_Show()
{
    Graph_Show(ui->widget);
}

void Curve::Graph_Show(QCustomPlot *CustomPlot)
{

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select * from information1");
    int k=model->rowCount();
    QVector<double> temp(k);
    QVector<double> temp4(k);
    QSqlQuery query;
    query.exec("select * from information1"); // 查询的结果可能不止一条记录，所以我们称之为结果集
    query.last();
    for(int i=0;i<k;i++){
        temp4[k-1-i]=i;
    }
    double temperture = query.value(1).toDouble(); //取第i条记录第1个字段(从0开始计数)的结果
    temp[k-1]=temperture;//when we fuzhi gei container,we shoule use the"[]"
    for(int j=0;j<k;j++)
    {
        if(query.previous())
        {
            double temperture = query.value(1).toDouble(); //取第i条记录第1个字段(从0开始计数)的结果
            temp[k-1-j]=temperture;//when we fuzhi gei container,we shoule use the"[]"
        }
     }
    CustomPlot->addGraph();
    CustomPlot->graph(0)->setPen(QPen(Qt::red));
    CustomPlot->graph(0)->setData(temp4,temp);
    CustomPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    CustomPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    CustomPlot->xAxis->setLabel("time");
    CustomPlot->yAxis->setLabel("temperture");
    CustomPlot->xAxis->setRange(0,k);
    CustomPlot->yAxis->setRange(0,100);
    CustomPlot->replot();
}
