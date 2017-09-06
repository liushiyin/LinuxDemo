#ifndef SELECTSHAPE_H
#define SELECTSHAPE_H

#include <QWidget>
#include"qmylabel.h"
#include<QGridLayout>
#include<QDir>

namespace Ui {
class SelectShape;
}

class SelectShape : public QWidget
{
    Q_OBJECT

public:
    explicit SelectShape(QWidget *parent = 0);
    ~SelectShape();

private:
    Ui::SelectShape *ui;

    QMyLabel *label;
};

#endif // SELECTSHAPE_H
