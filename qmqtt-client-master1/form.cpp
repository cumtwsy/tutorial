#include "form.h"
#include "ui_form.h"
#include<QSqlQueryModel>
#include<QTableView>
#include<QDebug>
#include<QVector>
#include "qcustomplot.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    //关联定时器溢出信号和相应的槽函数
    connect(timer, SIGNAL(timeout()), this, SLOT(timer()));
    timer->start(4000);
    QObject::connect(ui->selectBtn,SIGNAL(clicked(bool)),this,SLOT(timerUpdate()));
    QDateTime time = QDateTime::currentDateTime();
    QString str1 =time.toString("yyyy");
    QString str2 =time.toString("MM");
    QString str3 =time.toString("dd");
    ui->comboBox_Year->setCurrentText(str1);
    ui->comboBox_Month->setCurrentText(str2);
    ui->comboBox_Day->setCurrentText(str3);
}

Form::~Form()
{
    delete ui;
}

void Form::timerUpdate()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString year=ui->comboBox_Year->currentText().toUtf8();
    QString month=ui->comboBox_Month->currentText().toUtf8();
    QString day=ui->comboBox_Day->currentText().toUtf8();
    QString s4="table"+year+month+day;
    model->setQuery(QString("select * from `%1`").arg(s4));
    int i=model->rowCount();
    if(i>0){
    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
    }
    else QMessageBox::information(NULL, tr("基于MQTT喷灌机远程控制系统"),tr("喷灌机在此日期下没有作业！请重新输入日期！"));
}

void Form::timer()
{
    QString year=ui->comboBox_Year->currentText().toUtf8();
    QString month=ui->comboBox_Month->currentText().toUtf8();
    QString day=ui->comboBox_Day->currentText().toUtf8();
    QString s4="table"+year+month+day;
    QSqlQuery query1;
    //query1.exec(QString("select * from `%1`").arg(s4)); // 查询的结果可能不止一条记录，所以我们称之为结果集
    query1.exec("select * from table20170509");
    if(query1.first())//这一句很重要，我们可以通过这一句激活结果集的记录
    {
        query1.last();
    }
    QString temperature = query1.value(1).toString(); //取第i条记录第1个字段(从0开始计数)的结果
    QString humidity=query1.value(2).toString();
    QString light=query1.value(3).toString();
    QString pressure=query1.value(4).toString();
    ui->label_2->setText("10");
    ui->label_4->setText(temperature);
    ui->label_6->setText(humidity);
    ui->label_13->setText(light);
    ui->label_14->setText(pressure);
}


void Form::on_pushButton_2_clicked()
{
    QCustomPlot *widget=new QCustomPlot();
    widget->setMinimumSize(600,400);
    widget->setSelectionTolerance(5);
    widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select * from table20170509");
    int k=model->rowCount();
    QVector<double> temp(k);
    QVector<double> temp4(k);
    QSqlQuery query;
    query.exec("select * from table20170509"); // 查询的结果可能不止一条记录，所以我们称之为结果集
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
    widget->addGraph();
    widget->graph(0)->setPen(QPen(Qt::red));
    widget->graph(0)->setData(temp4,temp);
    widget->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    widget->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    widget->xAxis->setLabel("time");
    widget->yAxis->setLabel("temperture");
    widget->xAxis->setRange(0,k);
    widget->yAxis->setRange(0,100);
    widget->replot();
    widget->show();
}

void Form::on_pushButton_3_clicked()
{
    QWidget *window = new QWidget;
    QCustomPlot *widget=new QCustomPlot();
    QCustomPlot *widget2=new QCustomPlot();
    QCustomPlot *widget3=new QCustomPlot();
    QCustomPlot *widget4=new QCustomPlot();
    widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);
    widget2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);
    widget3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);
    widget4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);
    widget->setMinimumSize(600,400);
    widget2->setMinimumSize(600,400);
    widget3->setMinimumSize(600,400);
    widget4->setMinimumSize(600,400);
    widget->setWindowTitle("The curve of the temperture.");
    widget2->setWindowTitle("The curve of the humlity.");
    widget3->setWindowTitle("The curve of the light.");
    widget4->setWindowTitle("The curve of the pressure.");
    QHBoxLayout *layout = new QHBoxLayout;
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout->addWidget(widget);
    layout->addWidget(widget2);
    layout2->addWidget(widget3);
    layout2->addWidget(widget4);
    QVBoxLayout *layout3 = new QVBoxLayout;
    layout3->addLayout(layout);
    layout3->addLayout(layout2);
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
    query.exec("select * from table20170509"); // 查询的结果可能不止一条记录，所以我们称之为结果集
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
    widget->addGraph();
    widget->graph(0)->setPen(QPen(Qt::red));
    widget->graph(0)->setData(temp4,temp);
    widget->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    widget->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    widget->xAxis->setLabel("time");
    widget->yAxis->setLabel("temperture");
    widget->xAxis->setRange(0,10);
    widget->yAxis->setRange(0,100);
    widget->replot();
    //widget->show();
    widget2->addGraph();
    widget2->graph(0)->setPen(QPen(Qt::green));
    widget2->graph(0)->setData(temp4,temp1);
    widget2->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    widget2->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    widget2->xAxis->setLabel("time");
    widget2->yAxis->setLabel("humility");
    widget2->xAxis->setRange(0,10);
    widget2->yAxis->setRange(0,100);
    widget2->replot();
    //widget2->show();
    widget3->addGraph();
    widget3->graph(0)->setPen(QPen(Qt::blue));
    widget3->graph(0)->setData(temp4,temp2);
    widget3->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    widget3->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    widget3->xAxis->setLabel("time");
    widget3->yAxis->setLabel("light");
    widget3->xAxis->setRange(0,10);
    widget3->yAxis->setRange(0,1000);
    widget3->replot();
    //widget3->show();
    widget4->addGraph();
    widget4->graph(0)->setPen(QPen(Qt::black));
    widget4->graph(0)->setData(temp4,temp3);
    widget4->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    widget4->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(5)));
    widget4->xAxis->setLabel("time");
    widget4->yAxis->setLabel("pressure");
    widget4->xAxis->setRange(0,10);
    widget4->yAxis->setRange(0,1000);
    widget4->replot();
    //widget4->show();
    window->setLayout(layout3);
    window->show();
}




