#ifndef WINDOWTITLEBAR_H
#define WINDOWTITLEBAR_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class WindowTitleBar;
}

class WindowTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit WindowTitleBar(QWidget *parent = 0);
    ~WindowTitleBar();

private slots:
    void on_toolButton_3_clicked();

    void on_toolButton_2_clicked();

signals:
    void signalMin();

private:
    Ui::WindowTitleBar *ui;
};

#endif // WINDOWTITLEBAR_H
