#ifndef UTILITY_H
#define UTILITY_H

#include <QWidget>
#include <QObject>
#include <QPoint>
#include <QMouseEvent>
//macro to make no-window-title-bar windows have move ability,should be add in .h file which was a like-a widget
#define  WINDOW_NO_TITLE_BAR(CLASSNAME) \
protected: \
    QPoint m_windowPos; \
    QPoint m_mousePos; \
    QPoint m_dPos; \
    void mousePressEvent(QMouseEvent *event) \
                { \
        if (event->button() == Qt::LeftButton) \
                        {\
            m_windowPos = this->pos(); \
            m_mousePos = event->globalPos(); \
            m_dPos = m_mousePos - m_windowPos; \
            event->accept(); \
                        }\
                }; \
    void mouseMoveEvent(QMouseEvent *event) \
                { \
        if (event->buttons() & Qt::LeftButton) \
                                        {\
                                move(event->globalPos() - m_dPos); \
                                event->accept(); \
                                        }\
                };
namespace Ui {
class Utility;
}

class Utility : public QWidget
{
    Q_OBJECT

public:
    explicit Utility(QWidget *parent = 0);
    ~Utility();

private:
    Ui::Utility *ui;
};

#endif // UTILITY_H
