#include "connform.h"
#include "ui_connform.h"

ConnForm::ConnForm(QWidget *parent) :
    MqttForm(parent),
    ui(new Ui::ConnForm)
{
    ui->setupUi(this);
    ui->disconnButton->setEnabled(false);
    QHostInfo::lookupHost("m2m.eclipse.org",this, SLOT(lookedUp(QHostInfo)));
}

ConnForm::~ConnForm()
{
    delete ui;
}

void ConnForm::onConnect()
{
    //QString clientId = ui->leClientId->text();
    //QString username = ui->leUser->text();
    //QString passwd = ui->lePasswd->text();
    //QString willtopic = ui->leWillTopic->text();
    //QString willmsg = ui->teWillMsg->toPlainText();
    // New API do not use.
    //QMQTT::Will *will;
    //if(!_client->isConnectedToHost()) {
        //changes
        //API:  void setHost(const QHostAddress& host);
        //QHostAddress hostAdd(ui->leHost->text());
        //setCertification(host, PRIVATE_FILE);
        QString username="sunyang/penguanji";
        QString password="LSAEadnpLTooZzi/3UIL5dqkid4kgLFLNRAkMvqtSFg=";
        QHostAddress hostAdd("198.41.30.241");
        //QHostAddress hostAdd("192.168.1.102");
        quint16 port=1883;
        quint16 keeptime=200;
        _client->setHost(hostAdd);
        _client->setPort(port);
        _client->setKeepAlive(keeptime);
        _client->setUsername(username);
        _client->setPassword(password);
        _client->setCleanSession(true);
       /* //changes
        //API:  void setCleanSession(const bool cleansess);;
        //_client->setCleanSession(ui->cbCleanSess->isChecked());
        //if(!clientId.isEmpty())  _client->setClientId(clientId);
        //if(!username.isEmpty()) _client->setUsername(username);
        //if(!passwd.isEmpty()) _client->setPassword(passwd);
        //Use directly setWillTopic and setWillMessage.
        //if(!willtopic.isEmpty() && !willmsg.isEmpty()) {
            //New
            //API: void setWillTopic(const QString& willTopic);
            //API: void setWillQos(const quint8 willQos);
            //API: void setWillRetain(const bool willRetain);
            //API: void setWillMessage(const QString& willMessage);
           // _client->setWillTopic(willtopic);
            //_client->setWillMessage(willmsg);
        //}
        //changes
        //API:  void connectToHost();*/
        _client->connectToHost();
   // }
}

void ConnForm::onDisconnect()
{
    //changes
    //API:  bool isConnectedToHost() const;
    if(_client->isConnectedToHost()) {
        //change disconnected() to disconnectFromHost()
        _client->disconnectFromHost();
    }
}

void ConnForm::updateUiStatus()
{
    //changes
    //API:  bool isConnectedToHost() const;
    ui->connButton->setEnabled(!_client->isConnectedToHost());
    ui->disconnButton->setEnabled(_client->isConnectedToHost());
}

void ConnForm::lookedUp(QHostInfo host_info)
{
        if (host_info.error() != QHostInfo::NoError)
        {
             qDebug() << "Lookup failed:" << host_info.errorString();
             return;
        }

        for (int i = 0;i < host_info.addresses().size();i++)
        {
             qDebug() << "Found address:" << host_info.addresses()[i].toString() << endl;
        }
        ip=host_info.addresses()[0].toString();
}


