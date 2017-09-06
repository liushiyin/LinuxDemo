#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

namespace Ui {
class PaintWidget;
}

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

private:
    Ui::PaintWidget *ui;
};

#endif // PAINTWIDGET_H
