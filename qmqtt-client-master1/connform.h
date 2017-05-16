#ifndef CONNFORM_H
#define CONNFORM_H

#include <QWidget>
#include "mqttform.h"
#include <QHostInfo>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class ConnForm;
}

class ConnForm : public MqttForm
{
    Q_OBJECT
    
public:
    explicit ConnForm(QWidget *parent = 0);
    QString ip;
    ~ConnForm();

public slots:
    void updateUiStatus();
    void lookedUp(QHostInfo host_info);

private slots:
    void onConnect();
    void onDisconnect();


private:
    Ui::ConnForm *ui;
};

#endif // CONNFORM_H
