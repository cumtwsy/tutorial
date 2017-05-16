#include "pubform.h"
#include "ui_pubform.h"

PubForm::PubForm(QWidget *parent) :
    MqttForm(parent),
    ui(new Ui::PubForm)
{
    ui->setupUi(this);
    onPublishReady();
    ui->pushButton->setShortcut(QKeySequence(tr("Ctrl+P")));
}

PubForm::~PubForm()
{
    delete ui;
}

void PubForm::onPublishReady()
{
    ui->pushButton->setEnabled(true);
}

void PubForm::onPublish()
{
    QByteArray str = ui->comboBox->currentText().toUtf8();
    QByteArray str2="1";
    QMQTT::Message msg(0, "control_code",str+str2);         //给函数传参数的时候一定要知道函数的原型，一定要注意的函数的原型，赋值的时候。
    _client->publish(msg);
}

void PubForm::onTingPublish()
{
    QByteArray str = ui->comboBox->currentText().toUtf8();
    QByteArray str2="2";
    QMQTT::Message msg(0, "control_code",str+str2);
    //QMQTT::Message msg(0, "control_code","12");
    _client->publish(msg);
}

void PubForm::onJiPublish()
{
    QByteArray str = ui->comboBox->currentText().toUtf8();
    QByteArray str2="3";
    QMQTT::Message msg(0, "control_code",str+str2);
    _client->publish(msg);
}

void PubForm::onYiPublish()
{
    QByteArray str = ui->comboBox->currentText().toUtf8();
    QByteArray str2="4";
    QMQTT::Message msg(0, "control_code",str+str2);
    _client->publish(msg);
}

void PubForm::onErPublish()
{
    QByteArray str = ui->comboBox->currentText().toUtf8();
    QByteArray str2="5";
    QMQTT::Message msg(0, "control_code",str+str2);
    _client->publish(msg);
}

void PubForm::onSanPublish()
{
    QByteArray str = ui->comboBox->currentText().toUtf8();
    QByteArray str2="6";
    QMQTT::Message msg(0, "control_code",str+str2);
    _client->publish(msg);
}

void PubForm::lineEditSetFocus()
{

}
