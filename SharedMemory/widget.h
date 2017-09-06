#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSharedMemory>
#include<QFileDialog>
#include<QMessageBox>
#include<QApplication>
#include<QDesktopWidget>
#include<QImage>
#include<QPixmap>
#include<QBuffer>
#include<QDataStream>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    virtual ~Widget();


private slots:
    void on_loadBtn_clicked();

    void on_displayBtn_clicked();

private:
    void datech();
private:
    Ui::Widget *ui;
    QSharedMemory shareMemory;
};

#endif // WIDGET_H
