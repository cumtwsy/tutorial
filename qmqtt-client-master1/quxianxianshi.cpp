#include "quxianxianshi.h"
#include "ui_quxianxianshi.h"


QuXianxianshi::QuXianxianshi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuXianxianshi)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer();
    timer->start(2000);
    ui->widget_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->widget_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->widget_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    connect(timer,SIGNAL(timeout()),this,SLOT(Graph_Show()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Graph_Show1()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Graph_Show2()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Graph_Show3()));
    connect(ui->widget_1, SIGNAL(mouseRelease(QMouseEvent*)),
                   this, SLOT(slot_mouseRelese(QMouseEvent*)));
}

QuXianxianshi::~QuXianxianshi()
{
    delete ui;
}

void QuXianxianshi::Graph_Show()
{
    Graph_Show(ui->widget_1);
}

void QuXianxianshi::Graph_Show1()
{
    Graph_Show1(ui->widget_2);
}

void QuXianxianshi::Graph_Show2()
{
    Graph_Show2(ui->widget_3);
}

void QuXianxianshi::Graph_Show3()
{
    Graph_Show3(ui->widget_4);
}

void QuXianxianshi::Graph_Show(QCustomPlot *CustomPlot)
{

    QVector<double> temp(10);
    QVector<double> temp1(10);
    QVector<double> temp2(10);
    QVector<double> temp3(10);
    QVector<double> temp4(10);
    for(double i=0.0;i<=9.0;i++)
    {
        temp4[i]=i;
    }
    QSqlQuery query;
    query.exec("select * from information1"); // 查询的结果可能不止一条记录，所以我们称之为结果集
    query.last();
    double temperture = query.value(1).toDouble(); //取第i条记录第1个字段(从0开始计数)的结果
    double humility = query.value(2).toDouble(); //取第i条记录第2个字段的结果
    double light = query.value(3).toDouble();
    double pressure = query.value(4).toDouble();
    temp[9]=temperture;//when we fuzhi gei container,we shoule use the"[]"
    temp1[9]=humility;
    temp2[9]=light;
    temp3[9]=pressure;

    for(int j=0;j<=8;j++)
    {
        if(query.previous())
        {
        double temperture = query.value(1).toDouble(); //取第i条记录第1个字段(从0开始计数)的结果
        double humility = query.value(2).toDouble(); //取第i条记录第2个字段的结果
        double light = query.value(3).toDouble();
        double pressure = query.value(4).toDouble();
        temp[8-j]=temperture;//when we fuzhi gei container,we shoule use the"[]"
        temp1[8-j]=humility;
        temp2[8-j]=light;
        temp3[8-j]=pressure;
        }
     }
    CustomPlot->addGraph();
    CustomPlot->graph(0)->setPen(QPen(Qt::red));
    CustomPlot->graph(0)->setData(temp4,temp);
    CustomPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    CustomPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    CustomPlot->xAxis->setLabel("number");
    CustomPlot->yAxis->setLabel("temperture");
    CustomPlot->xAxis->setRange(0,9);
    CustomPlot->yAxis->setRange(0,100);
    CustomPlot->replot();
}

void QuXianxianshi::Graph_Show1(QCustomPlot *CustomPlot)
{
    QVector<double> temp(10);
    QVector<double> temp1(10);
    QVector<double> temp2(10);
    QVector<double> temp3(10);
    QVector<double> temp4(10);
    for(double i=0.0;i<=9.0;i++)
    {
        temp4[i]=i;
    }
    QSqlQuery query;
    query.exec("select * from information1"); // 查询的结果可能不止一条记录，所以我们称之为结果集
    query.last();
    double temperture = query.value(1).toDouble(); //取第i条记录第1个字段(从0开始计数)的结果
    double humility = query.value(2).toDouble(); //取第i条记录第2个字段的结果
    double light = query.value(3).toDouble();
    double pressure = query.value(4).toDouble();
    temp[9]=temperture;//when we fuzhi gei container,we shoule use the"[]"
    temp1[9]=humility;
    temp2[9]=light;
    temp3[9]=pressure;
    for(int j=0;j<=8;j++)
    {
        if(query.previous())
        {
        double temperture = query.value(1).toDouble(); //取第i条记录第1个字段(从0开始计数)的结果
        double humility = query.value(2).toDouble(); //取第i条记录第2个字段的结果
        double light = query.value(3).toDouble();
        double pressure = query.value(4).toDouble();
        temp[8-j]=temperture;//when we fuzhi gei container,we shoule use the"[]"
        temp1[8-j]=humility;
        temp2[8-j]=light;
        temp3[8-j]=pressure;
        }
     }
    CustomPlot->addGraph();
    CustomPlot->graph(0)->setPen(QPen(Qt::blue));
    CustomPlot->graph(0)->setData(temp4,temp1);
    CustomPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    CustomPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    CustomPlot->xAxis->setLabel("number");
    CustomPlot->yAxis->setLabel("humility");
    CustomPlot->xAxis->setRange(0,9);
    CustomPlot->yAxis->setRange(0,100);
    CustomPlot->replot();
}

void QuXianxianshi::Graph_Show2(QCustomPlot *CustomPlot)
{
    QVector<double> temp(10);
    QVector<double> temp1(10);
    QVector<double> temp2(10);
    QVector<double> temp3(10);
    QVector<double> temp4(10);
    for(double i=0.0;i<=9.0;i++)
    {
        temp4[i]=i;
    }
    QSqlQuery query;
    query.exec("select * from information1"); // 查询的结果可能不止一条记录，所以我们称之为结果集
    query.last();
    double temperture = query.value(1).toDouble(); //取第i条记录第1个字段(从0开始计数)的结果
    double humility = query.value(2).toDouble(); //取第i条记录第2个字段的结果
    double light = query.value(3).toDouble();
    double pressure = query.value(4).toDouble();
    temp[9]=temperture;//when we fuzhi gei container,we shoule use the"[]"
    temp1[9]=humility;
    temp2[9]=light;
    temp3[9]=pressure;
    for(int j=0;j<=8;j++)
    {
        if(query.previous())
        {
        double temperture = query.value(1).toDouble(); //取第i条记录第1个字段(从0开始计数)的结果
        double humility = query.value(2).toDouble(); //取第i条记录第2个字段的结果
        double light = query.value(3).toDouble();
        double pressure = query.value(4).toDouble();
        temp[8-j]=temperture;//when we fuzhi gei container,we shoule use the"[]"
        temp1[8-j]=humility;
        temp2[8-j]=light;
        temp3[8-j]=pressure;
        }
     }
    CustomPlot->addGraph();
    CustomPlot->graph(0)->setPen(QPen(Qt::yellow));
    CustomPlot->graph(0)->setData(temp4,temp2);
    CustomPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    CustomPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    CustomPlot->xAxis->setLabel("number");
    CustomPlot->yAxis->setLabel("light");
    CustomPlot->xAxis->setRange(0,9);
    CustomPlot->yAxis->setRange(0,1000);
    CustomPlot->replot();
}

void QuXianxianshi::Graph_Show3(QCustomPlot *CustomPlot)
{
    QVector<double> temp(10);
    QVector<double> temp1(10);
    QVector<double> temp2(10);
    QVector<double> temp3(10);
    QVector<double> temp4(10);
    for(double i=0.0;i<=9.0;i++)
    {
        temp4[i]=i;
    }
    QSqlQuery query;
    query.exec("select * from information1"); // 查询的结果可能不止一条记录，所以我们称之为结果集
    query.last();
    double temperture = query.value(1).toDouble(); //取第i条记录第1个字段(从0开始计数)的结果
    double humility = query.value(2).toDouble(); //取第i条记录第2个字段的结果
    double light = query.value(3).toDouble();
    double pressure = query.value(4).toDouble();
    temp[9]=temperture;//when we fuzhi gei container,we shoule use the"[]"
    temp1[9]=humility;
    temp2[9]=light;
    temp3[9]=pressure;
    for(int j=0;j<=8;j++)
    {
        if(query.previous())
        {
        double temperture = query.value(1).toDouble(); //取第i条记录第1个字段(从0开始计数)的结果
        double humility = query.value(2).toDouble(); //取第i条记录第2个字段的结果
        double light = query.value(3).toDouble();
        double pressure = query.value(4).toDouble();
        temp[8-j]=temperture;//when we fuzhi gei container,we shoule use the"[]"
        temp1[8-j]=humility;
        temp2[8-j]=light;
        temp3[8-j]=pressure;
        }
     }
    CustomPlot->addGraph();
    CustomPlot->graph(0)->setPen(QPen(Qt::green));
    CustomPlot->graph(0)->setData(temp4,temp3);
    CustomPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    CustomPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    CustomPlot->xAxis->setLabel("number");
    CustomPlot->yAxis->setLabel("pressure");
    CustomPlot->xAxis->setRange(0,9);
    CustomPlot->yAxis->setRange(0,1000);
    CustomPlot->replot();
}

void QuXianxianshi::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<event->pos();
}

void QuXianxianshi::slot_mouseRelese(QMouseEvent *event){
    ///排除非左鼠标键
    if (event->button() != Qt::LeftButton){        return;    }

    QPointF ChickedPoint = event->pos();
     ///排除区间外鼠标点
    if(!ui->widget_1->viewport().contains(event->pos())){        return;    }


    QPointF closest(INT_MAX, INT_MAX);
     qreal distance(INT_MAX);
     QCPDataMap* m_graphDataMap1 = ui->widget_1->graph(0)->data();
     QCPDataMapIterator itr(*m_graphDataMap1);
     while(itr.hasNext()){
           itr.next();
          qreal dPosX = ui->widget_1->xAxis->coordToPixel(itr.key());
          qreal dPosY = ui->widget_1->yAxis->coordToPixel(itr.value().value);


           QPointF currentPoint(dPosX, dPosY);
           qreal currentDistance = qSqrt((currentPoint.x()-ChickedPoint.x()) * (currentPoint.x()-ChickedPoint.x()) +
                             (currentPoint.y()-ChickedPoint.y()) * (currentPoint.y()-ChickedPoint.y()));


        if(currentDistance < distance){
           distance = currentDistance;
           closest  = currentPoint;
        }
   }
     ///可放开调试信息，观察鼠标点击到折线的距离。
    ///qDebug()<<"------pos-------"<<distance;
    if(distance > ui->widget_1->selectionTolerance()){        return;    }


     double dKey = ui->widget_1->xAxis->pixelToCoord(closest.x());
     double dValue = ui->widget_1->yAxis->pixelToCoord(closest.y());


    ///添加到散点折线图中
    ui->widget_1->graph(1)->removeData(dKey);
    ui->widget_1->graph(1)->addData(dKey, dValue);
    QCPItemText *m_pMousValue = new QCPItemText(ui->widget_1);
    m_pMousValue->setText(QString("X: %1, Y: %2").arg(dKey).arg(dValue));
}
