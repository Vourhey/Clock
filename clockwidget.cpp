#include <QApplication>
#include <QSettings>
#include <QtGui>
#include "clockwidget.h"

ClockWidget::ClockWidget(QWidget *parent) :
    QWidget(parent), press(false)
{
    // полупрозрачный фон
    setAttribute(Qt::WA_TranslucentBackground, true);
    // без границ и заголовка
    setWindowFlags(Qt::ToolTip);

    restoreState();

    // обновляем каждую секунду
    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), SLOT(update()));
    timer->start(1000);
}

ClockWidget::~ClockWidget()
{
    saveState();
}

void ClockWidget::saveState()
{
    QSettings s(tr("VourheyApp"), tr("Clock"));
    s.beginGroup("ClockWidget");
    s.setValue("pos", pos());
    s.setValue("size", size());
    s.setValue("color", color.name());
    s.endGroup();
}

void ClockWidget::restoreState()
{
    QSettings s(tr("VourheyApp"), tr("Clock"));
    s.beginGroup("ClockWidget");

    QPoint pos = s.value("pos", QPoint(100,100)).toPoint();
    move(pos);

    QSize size = s.value("size", QSize(200,200)).toSize();
    resize(size);

    // синий по умолчанию
    QColor cl = s.value("color", QString("#0000FF")).toString();
    setColor(cl);

    s.endGroup();
}

// цвет циферблата и стрелочек
void ClockWidget::setColor(QColor cl)
{
    color = cl;
}

// отрисовываем часы
void ClockWidget::paintEvent(QPaintEvent *)
{
    QTime ctime = QTime::currentTime();
    int h = this->height();
    int w = this->width();
    int r = qMin(h,w) / 2 - 4;
    QPoint center(w/2, h/2);
    QPen pen;
    pen.setWidth(5);
    pen.setColor(color);
    pen.setCapStyle(Qt::RoundCap);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(pen);
    p.drawEllipse(center, r, r); // рисуем окрузность

    p.translate(center);
    p.scale(qMin(h,w) / 200, qMin(h,w) / 200);

    // рисуем часовую стрелку
    p.save();
    qreal offh = ctime.hour() + ctime.minute() / 60.0 ;
    p.rotate(30.0 * offh);
    p.drawLine(0, 0, 0, -50);
    p.restore();

    // минутную
    qreal offm = ctime.minute() + ctime.second() / 60.0;
    p.rotate(6.0 * offm);
    p.drawLine(0,0, 0, -90);
}

// меняет цвет циферблата и стрелочек
void ClockWidget::setColorDialog()
{
    setColor(QColorDialog::getColor(color, this, tr("Choose color")));
}

// контекстное мени
void ClockWidget::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu menu(this);

    menu.addAction(tr("Choose color..."), this, SLOT(setColorDialog()));
    menu.addSeparator();

    QMenu *submenu = menu.addMenu(tr("Copy time to clipboard"));
    submenu->addAction(tr("hh:mm:ss"), this, SLOT(copyToClipSlot()));
    submenu->addAction(tr("hh:mm"), this, SLOT(copyToClipSlot()));
    submenu->addAction(tr("hh:mm:ss AP"), this, SLOT(copyToClipSlot()));
    submenu->addAction(tr("hh:mm AP"), this, SLOT(copyToClipSlot()));
    submenu->addAction(tr("hh.mm.ss"), this, SLOT(copyToClipSlot()));
    submenu->addAction(tr("hh.mm"), this, SLOT(copyToClipSlot()));
    submenu->addAction(tr("hh.mm.ss AP"), this, SLOT(copyToClipSlot()));
    submenu->addAction(tr("hh.mm AP"), this, SLOT(copyToClipSlot()));

    menu.addSeparator();
    // поддерживаем выход (заголовка теперь-то нет)
    menu.addAction(tr("Quit"), qApp, SLOT(quit()));

    menu.exec(e->globalPos());
}

// следующие 3 функции (mouse*) поддерживают перетаскивание
// окна в любом месте
void ClockWidget::mouseMoveEvent(QMouseEvent *e)
{
    if((e->buttons() & Qt::LeftButton) && press)
        move(e->globalX()-lastPoint.x(), e->globalY()-lastPoint.y());
}

void ClockWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        lastPoint = e->pos();
        press = true;
    }
}

void ClockWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && press)
        press = false;
}

// копирует время в буфер обмена
void ClockWidget::copyToClipSlot()
{
    QAction *act = qobject_cast<QAction*>(sender());

    QTime ctime = QTime::currentTime();
    QString time = ctime.toString(act->text());
    QClipboard *clip = QApplication::clipboard();
    clip->setText(time);
}
