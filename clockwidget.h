#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QColor>

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

private:
    void saveState();
    void restoreState();

protected:
    void paintEvent(QPaintEvent *);
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    bool press;
    QPoint lastPoint;
    QColor color;
};

#endif // CLOCKWIDGET_H
