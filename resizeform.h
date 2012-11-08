#ifndef RESIZEFORM_H
#define RESIZEFORM_H

#include <QDialog>

class QSpinBox;
class QPushButton;

class ResizeForm : public QDialog
{
    Q_OBJECT
public:
    explicit ResizeForm(int size, QWidget *parent = 0);

    QSpinBox *getSpinBox() const;
    
signals:
    
public slots:
    
private:
    QSpinBox *spin;
    QPushButton *button;
};

#endif // RESIZEFORM_H
