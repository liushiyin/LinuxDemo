#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   ui->listWidget->setViewMode(QListView::IconMode);
    this->move((QApplication::desktop()->width()-this->width())/2,
               (QApplication::desktop()->height()-this->height())/2);
   connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEdit_returnPressed()
{
    on_addBtn_clicked();
}

void Widget::on_addBtn_clicked()
{
    QListWidgetItem *item=new QListWidgetItem;
    item->setText(ui->lineEdit->text());
    item->setIcon(QIcon(QDir::currentPath()+"/images/"+item->text()+".png"));
    ui->listWidget->addItem(item);
    ui->lineEdit->clear();
}

void Widget::on_deleteBtn_clicked()
{
    ui->listWidget->removeItemWidget(ui->listWidget->takeItem(ui->listWidget->currentRow()));
}

void	Widget::itemClicked(QListWidgetItem * item)
{
    QMessageBox::information(this,"",item->text());
}
