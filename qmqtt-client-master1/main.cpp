#include <QCoreApplication>
#include <QApplication>
#include <QFile>

#include "QMqtt/qmqtt.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("基于MQTT喷灌机远程控制系统");
    QCoreApplication::setApplicationName("基于MQTT喷灌机远程控制系统");
    QApplication a(argc, argv);
    MainWindow w(new QMQTT::Client());
    QString qss;
    QFile qssFile(":/ui/white.qss");
    qssFile.open(QFile::ReadOnly);

        if(qssFile.isOpen())

        {

            qss = QLatin1String(qssFile.readAll());

            qApp->setStyleSheet(qss);

            qssFile.close();

        }
    w.setWindowTitle("基于MQTT喷灌机远程控制系统");
    w.show();
    return a.exec();
}
