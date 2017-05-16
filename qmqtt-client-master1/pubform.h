#ifndef PUBFORM_H
#define PUBFORM_H

#include <QWidget>
#include "mqttform.h"

namespace Ui {
class PubForm;
}

class PubForm : public MqttForm
{
    Q_OBJECT
    
public:
    explicit PubForm(QWidget *parent = 0);
    ~PubForm();
    void lineEditSetFocus();

public slots:
    void onPublishReady();
    void onPublish();
    void onTingPublish();
    void onJiPublish();
    void onYiPublish();
    void onErPublish();
    void onSanPublish();

private:
    Ui::PubForm *ui;
};

#endif // PUBFORM_H
