#include "windowtitlebar.h"
#include "ui_windowtitlebar.h"

WindowTitleBar::WindowTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowTitleBar)
{
    ui->setupUi(this);
}

WindowTitleBar::~WindowTitleBar()
{
    delete ui;
}

void WindowTitleBar::on_toolButton_3_clicked()
{
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
}



void WindowTitleBar::on_toolButton_2_clicked()
{
    emit signalMin();
}
