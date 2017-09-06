#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->timer=new QTimer;
    connect(this->timer,SIGNAL(timeout()),this,SLOT(getClipboard()));
    this->timer->start(200);
}

Widget::~Widget()
{
    delete timer;
    delete ui;
}

 void Widget::getClipboard()
 {
     pixmap=QApplication::clipboard()->pixmap();
     ui->pixLabel->setPixmap(pixmap.scaled(QSize(ui->pixLabel->width(),ui->pixLabel->height())));
 }
