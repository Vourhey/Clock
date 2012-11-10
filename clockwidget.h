#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QColor>
#include "resizeform.h"
#include <QTime>

class QCalendarWidget;

class ClockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClockWidget(QWidget *parent = 0);
    ~ClockWidget();

    void setColor(QColor cl);

private slots:
    void setColorDialog();
    void copyToClipSlot();
    void resizeSlot();
    void chengeSize(int);

private:
    void saveState();
    void restoreState();

protected:
    void paintEvent(QPaintEvent *);
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
    bool press;
    QPoint lastPoint;
    QColor color;
    ResizeForm *rf;
    QTime ctime;
    QCalendarWidget *calendar;
};

#endif // CLOCKWIDGET_H
