#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QApplication>
#include<QClipboard>
#include<QSize>
#include<QPixmap>
#include<QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void getClipboard();

private:
    Ui::Widget *ui;
    QTimer* timer;
    QPixmap pixmap;
};

#endif // WIDGET_H
