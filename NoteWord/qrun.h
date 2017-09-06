#ifndef QRUN_H
#define QRUN_H

#include <QWidget>

namespace Ui {
class QRun;
}

class QRun : public QWidget
{
    Q_OBJECT

public:
    explicit QRun(QWidget *parent = 0);
    ~QRun();

private:
    Ui::QRun *ui;
};

#endif // QRUN_H
