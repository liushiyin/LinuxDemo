#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Shared Memory");
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_loadBtn_clicked()
{
    if(shareMemory.isAttached())
    {
        shareMemory.detach();
    }
    QString fileName=QFileDialog::getOpenFileName(this,"上传",QDir::currentPath(),"images(*.png *.xpm *.gif)");
    QImage image;
    if(!image.load(fileName))
    {
        QMessageBox::information(this,"提示","加载文件错误！");
    }
    ui->displayLabel->setPixmap(QPixmap::fromImage(image));
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out<<image;
    int size=buffer.size();
    if(!shareMemory.create(size))
    {
        QMessageBox::information(this,"提示",shareMemory.errorString());
        return;
    }
    shareMemory.lock();
    char *to=(char*)shareMemory.data();
    const char *from= buffer.data().data();
    memcpy(to,from,qMin(shareMemory.size(),size));
    shareMemory.unlock();
}

void Widget::on_displayBtn_clicked()
{
    if(!shareMemory.attach())
    {
        QMessageBox::information(this,"提示","无法从共享内存获取数据");
        return;
    }
    QBuffer buffer;
    QDataStream in(&buffer);
    QImage image;
    shareMemory.lock();
    buffer.setData((char*)shareMemory.constData(),shareMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in>>image;
    shareMemory.unlock();
    ui->displayLabel->setPixmap(QPixmap::fromImage(image));
}
