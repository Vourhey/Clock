#include <QtGui>
#include "resizeform.h"

ResizeForm::ResizeForm(int size, QWidget *parent) :
    QDialog(parent)
{
    spin = new QSpinBox;
    button = new QPushButton(tr("Ok"));

    spin->setMinimum(120);
    spin->setMaximum(500);
    spin->setValue(size);

    connect(button, SIGNAL(clicked()), this, SLOT(hide()));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(spin);
    layout->addWidget(button);

    setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowTitleHint );
    setFixedSize(100, 100);
}

QSpinBox *ResizeForm::getSpinBox() const
{
    return spin;
}
