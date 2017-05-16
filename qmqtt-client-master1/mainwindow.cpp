#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cJSON.h"

MainWindow::MainWindow(QMQTT::Client *client, QWidget *parent) :
    QMainWindow(parent),
    _client(client),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->conForm->init(client);
    ui->pubForm->init(client);
    ui->subForm->init(client);

    this->setMaximumSize(1020,750);
    this->setMinimumSize(1020,750);


    //add pushBtuoon slots
    connect(ui->pushButtonConnect,SIGNAL(clicked(bool)),this,SLOT(connectServer()));
    connect(ui->pushButtonPusblish,SIGNAL(clicked(bool)),this,SLOT(publishTopic()));
    connect(ui->pushButtonSubscribe,SIGNAL(clicked(bool)),this,SLOT(subscribeTopic()));
    connect(ui->pushButtonQuit,SIGNAL(clicked(bool)),this,SLOT(quitApp()));
    connect(ui->pushButtonClear,SIGNAL(clicked(bool)),this,SLOT(clearMsg()));
    connect(ui->pushButtonAbout,SIGNAL(clicked(bool)),this,SLOT(aboutApp()));
    connect(ui->baoButton,SIGNAL(clicked(bool)),this,SLOT(baobiao()));

    //connform slots
    connect(_client, SIGNAL(disconnected()), ui->conForm, SLOT(updateUiStatus()));
    connect(_client, SIGNAL(connected()), ui->conForm, SLOT(updateUiStatus()));
    //mainwindow slots
    connect(_client, SIGNAL(connected()), this, SLOT(onMQTT_Connected()));

    //todo: should emit on server suback
    //connect(_client, SIGNAL(connacked(quint8)), this, SLOT(onMQTT_Connacked(quint8)));
    connect(_client, SIGNAL(error(QMQTT::ClientError)), this, SLOT(onMQTT_error(QMQTT::ClientError)));

    //slots changes
    //API:  void published(const QMQTT::Message& message);
    connect(_client,SIGNAL(published(const QMQTT::Message &)),this,SLOT(onMQTT_Published(const QMQTT::Message &)));

    //todo: should emit on server suback
    connect(_client, SIGNAL(pubacked(quint8, quint16)), this, SLOT(onMQTT_Pubacked(quint8, quint16)));
    connect(_client, SIGNAL(received(const QMQTT::Message &)), this, SLOT(onMQTT_Received(const QMQTT::Message &)));
    connect(_client, SIGNAL(subscribed(const QString &)), this, SLOT(onMQTT_subscribed(const QString &)));

    //todo: should emit on server suback
    //connect(_client, SIGNAL(subacked(quint16, quint8)), this, SLOT(onMQTT_subacked(quint16, quint8)));
    connect(_client, SIGNAL(unsubscribed(const QString &)), this, SLOT(onMQTT_unsubscribed(const QString &)));
    //todo: should emit on server suback
    //connect(_client, SIGNAL(unsubacked(quint16)), this, SLOT(onMQTT_unsubacked(quint16)));
    //connect(_client, SIGNAL(pong()), this, SLOT(onMQTT_Pong()));
    connect(_client, SIGNAL(disconnected()), this, SLOT(onMQTT_disconnected()));
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("information1");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open())
        qDebug() << "Failed to connect to root mysql admin";
    else qDebug() << "open";
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());//去掉窗口边框
    connect(ui->widget,&WindowTitleBar::signalMin,this,&MainWindow::minisize);
    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(-5, 5);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(8);
    QGraphicsDropShadowEffect *shadow_effect1 = new QGraphicsDropShadowEffect(this);
    shadow_effect1->setOffset(-5, 5);
    shadow_effect1->setColor(Qt::gray);
    shadow_effect1->setBlurRadius(8);
    QGraphicsDropShadowEffect *shadow_effect3 = new QGraphicsDropShadowEffect(this);
    shadow_effect3->setOffset(-5, 5);
    shadow_effect3->setColor(Qt::gray);
    shadow_effect3->setBlurRadius(8);
    QGraphicsDropShadowEffect *shadow_effect4 = new QGraphicsDropShadowEffect(this);
    shadow_effect4->setOffset(-5, 5);
    shadow_effect4->setColor(Qt::gray);
    shadow_effect4->setBlurRadius(8);
    QGraphicsDropShadowEffect *shadow_effect5 = new QGraphicsDropShadowEffect(this);
    shadow_effect5->setOffset(-5, 5);
    shadow_effect5->setColor(Qt::gray);
    shadow_effect5->setBlurRadius(8);
    QGraphicsDropShadowEffect *shadow_effect6 = new QGraphicsDropShadowEffect(this);
    shadow_effect6->setOffset(-5, 5);
    shadow_effect6->setColor(Qt::gray);
    shadow_effect6->setBlurRadius(8);
    QGraphicsDropShadowEffect *shadow_effect7 = new QGraphicsDropShadowEffect(this);
    shadow_effect7->setOffset(-5, 5);
    shadow_effect7->setColor(Qt::gray);
    shadow_effect7->setBlurRadius(8);
    QGraphicsDropShadowEffect *shadow_effect8 = new QGraphicsDropShadowEffect(this);
    shadow_effect8->setOffset(-5, 5);
    shadow_effect8->setColor(Qt::gray);
    shadow_effect8->setBlurRadius(8);
    QGraphicsDropShadowEffect *shadow_effect9 = new QGraphicsDropShadowEffect(this);
    shadow_effect9->setOffset(-5, 5);
    shadow_effect9->setColor(Qt::gray);
    shadow_effect9->setBlurRadius(8);
    QGraphicsDropShadowEffect *shadow_effect10 = new QGraphicsDropShadowEffect(this);
    shadow_effect10->setOffset(-5, 5);
    shadow_effect10->setColor(Qt::gray);
    shadow_effect10->setBlurRadius(8);
    ui->pushButtonConnect->setGraphicsEffect(shadow_effect);
    //ui->widget->setGraphicsEffect(shadow_effect1);
    ui->pushButtonPusblish->setGraphicsEffect(shadow_effect9);
    ui->pushButtonAbout->setGraphicsEffect(shadow_effect3);
    ui->pushButtonConnect->setGraphicsEffect(shadow_effect4);
    ui->logConsole->setGraphicsEffect(shadow_effect5);
    ui->pushButtonClear->setGraphicsEffect(shadow_effect6);
    ui->pushButtonQuit->setGraphicsEffect(shadow_effect7);
    ui->pushButtonSubscribe->setGraphicsEffect(shadow_effect8);
    ui->baoButton->setGraphicsEffect(shadow_effect10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void addinformation(QSqlQuery &query,const QString &time ,double &tem,double &hum,double &lig,double &pre)

{
    //query.addBindValue(id);
    query.addBindValue(time);
    query.addBindValue(tem);
    query.addBindValue(hum);
    query.addBindValue(lig);
    query.addBindValue(pre);
    query.exec();
}
/* -----------------------------------------------------------
 MQTT Client Slots
 -----------------------------------------------------------*/
void MainWindow::onMQTT_Connected()
{
    log(tr("已经连接上服务器，服务器IP为： %1:%2").arg(_client->host().toString()).arg(_client->port()));
    //todo: should emit on server suback
    ui->pushButtonPusblish->setEnabled(true);
    ui->pushButtonSubscribe->setEnabled(true);
    ui->baoButton->setEnabled(true);
}



void MainWindow::onMQTT_Connacked(quint8 ack)
{
    //todo: should emit on server suback
    /*
    QString ackStatus;
    switch(ack) {
    case QMQTT::CONNACK_ACCEPT:
        ui->pushButtonPusblish->setEnabled(true);
        ui->pushButtonSubscribe->setEnabled(true);
        ackStatus = "Connection Accepted";
        break;
    case QMQTT::CONNACK_PROTO_VER:
        ackStatus = "Connection Refused: unacceptable protocol version";
        break;
    case QMQTT::CONNACK_INVALID_ID:
        ackStatus = "Connection Refused: identifier rejected";
        break;
    case QMQTT::CONNACK_SERVER:
        ackStatus = "Connection Refused: server unavailable";
        break;
    case QMQTT::CONNACK_CREDENTIALS:
        ackStatus = "Connection Refused: bad user name or password";
        break;
    case QMQTT::CONNACK_AUTH:
        ackStatus = "Connection Refused: not authorized";
        break;
    }
    log(tr("connacked: %1, %2").arg(ack).arg(ackStatus));
    */
}


void MainWindow::onMQTT_error(QMQTT::ClientError err)
{
    //todo: should emit on server suback
    /*
    QString errInfo;

    switch(err) {
    // 0	The connection was refused by the peer (or timed out).
    case QAbstractSocket::ConnectionRefusedError:
        errInfo = tr("Connection Refused");
    //	 1	The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.
    case QAbstractSocket::RemoteHostClosedError:
        errInfo = tr("Remote Host Closed");
    //	2	The host address was not found.
    case QAbstractSocket::HostNotFoundError:
        errInfo = tr("Host Not Found Error");
    // 	3	The socket operation failed because the application lacked the required privileges.
    case QAbstractSocket::SocketAccessError:
        errInfo = tr("Socket Access Error");
    // 	4	The local system ran out of resources (e.g., too many sockets).
    case QAbstractSocket::SocketResourceError:
        errInfo = tr("Socket Resource Error");
    // 	5	The socket operation timed out.
    case QAbstractSocket::SocketTimeoutError:
        errInfo = tr("Socket Timeout Error");
    default:
        errInfo = tr("Socket Error");
    }

    log(errInfo);
    */
}

void MainWindow::onMQTT_Published(const QMQTT::Message &message)
{
    log(tr("控制代码已经发送给喷灌机 %1").arg(message.topic()));
    //log(tr("控制代码: %1").arg(message.payload()));
    //printf("控制代码");
    log(message.payload());
}

void MainWindow::onMQTT_Pubacked(quint8 type, quint16 msgid)
{
    log(tr("pubacked: type=%1, msgid=%2").arg(type, msgid));
}

void MainWindow::onMQTT_Received(const QMQTT::Message &message)
{
    log(tr("来自喷灌机: %1 的详细信息, 订阅级别Qs%2").arg(message.topic()).arg(message.qos()));
    log(message.payload());
    //QString str2=message.payload();
    QDateTime time = QDateTime::currentDateTime();
    QString str =time.toString("yyyy-MM-dd hh:mm:ss");
    QString str5 =time.toString("yyyyMMdd");
    QString str6="table"+str5;
    cJSON *root = cJSON_Parse(message.payload());
     if(!root) {
        printf("get root faild !\n");
     }
    cJSON *temperature = cJSON_GetObjectItem(root, "temperature");
    double str1=temperature->valuedouble;
    cJSON *humidity = cJSON_GetObjectItem(root, "humidity");
    double str2=humidity->valuedouble;
    cJSON *light=cJSON_GetObjectItem(root,"light");
    double str3=light->valuedouble;
    cJSON *pressure=cJSON_GetObjectItem(root,"pressure");
    double str4=pressure->valuedouble;
    QSqlQuery query(db);
    /*query.exec("create table information5(time varchar(100),temperature double,humidity double,light double,pressure double)");//注意这里varchar一定要指定长度，不然会出错
    if (!query.prepare(QLatin1String("insert into information5(time,temperature,humidity,light,pressure) values(?, ?, ?, ?, ?)")))
         qDebug() << query.lastError();
    addinformation(query,str,str1,str2,str3,str4);*/
    /*query.prepare(QLatin1String("set @sqlstr = concat('create table TABLE1_',date_format(curdate(),'%Y%m%d'),' (id int)')"));
    query.prepare(QLatin1String("PREPARE stmt1 FROM @sqlstr"));
    query.prepare(QLatin1String("EXECUTE stmt1"));*/
    query.exec(QString("create table `%1`(time varchar(100),temperature double,humidity double,light double,pressure double)").arg(str6));//注意这里varchar一定要指定长度，不然会出错
        if (!query.prepare(QString("insert into `%1`(time,temperature,humidity,light,pressure) values(?, ?, ?, ?, ?)").arg(str6)))
             qDebug() << query.lastError();
        addinformation(query,str,str1,str2,str3,str4);


}

void MainWindow::onMQTT_subscribed(const QString &topic)
{
    log(tr("已经订阅喷灌机： %1").arg(topic));
}

void MainWindow::onMQTT_subacked(quint16 msgid, quint8 qos)
{
    log(tr("subacked: msgid=%1, qos=%2").arg(msgid).arg(qos));
}

void MainWindow::onMQTT_unsubscribed(const QString &topic)
{
    log(tr("unsubscribed %1").arg(topic));
}

void MainWindow::onMQTT_unsubacked(quint16 msgid)
{
    log(tr("unsubacked: msgid=%1").arg(msgid));
}

void MainWindow::onMQTT_Pong()
{
    log("pong received.");
}

void MainWindow::onMQTT_disconnected()
{
    ui->pushButtonPusblish->setEnabled(false);
    ui->pushButtonSubscribe->setEnabled(false);
    ui->baoButton->setEnabled(false);
    log("断开连接.");
}

/* -----------------------------------------------------------
 UI Action Slots
 -----------------------------------------------------------*/


void MainWindow::log(const QString & msg)
{
    ui->logConsole->append(msg);
}



void MainWindow::quitApp()
{
    QMessageBox msgBox;
    msgBox.setText("你确定要退出吗？");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret=msgBox.exec();
    //qApp->quit();
    switch (ret) {
      case QMessageBox::Ok:
          // Save was clicked
          qApp->quit();
          break;
      case QMessageBox::Cancel:
          // Cancel was clicked
          break;
      default:
          // should never be reached
          break;
    }
}

void MainWindow::connectServer()
{
     ui->stackedWidget->setCurrentWidget(ui->conForm);
}

void MainWindow::baobiao()
{
    ui->stackedWidget->setCurrentWidget(ui->baoForm);
}


void MainWindow::aboutApp()
{
    QMessageBox::information(NULL, tr("基于MQTT喷灌机远程控制系统"),
             tr("版本: V0.1.1\n\n"
                 "作者：cumtwsy \n\n"
                 "单位：中国矿业大学南湖校区机电工程学院\n"));
}

void MainWindow::clearMsg()
{
    ui->logConsole->clear();
}

void MainWindow::subscribeTopic()
{
    ui->stackedWidget->setCurrentWidget(ui->subForm);
    ui->subForm->clearLineEdit(); // also sets focus to lineEdit
}

void MainWindow::publishTopic()
{
    ui->stackedWidget->setCurrentWidget(ui->pubForm);
    ui->pubForm->lineEditSetFocus();
}

void MainWindow::on_actionAbout_triggered()
{
    aboutApp();
}

void MainWindow::on_actionQuit_triggered()
{
    //quitApp();
    QMessageBox msgBox;
    msgBox.setText("你确定要退出吗？");
    msgBox.setInformativeText("退出将无法对卷盘式喷灌机进行远程操作！！！");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret=msgBox.exec();
    switch (ret) {
      case QMessageBox::Ok:
          // Save was clicked
          qApp->quit();
          break;
      case QMessageBox::Cancel:
          // Cancel was clicked
          break;
      default:
          // should never be reached
          break;
    }
    this->hide();
}

void MainWindow::minisize()
{
    this->showMinimized();
}

