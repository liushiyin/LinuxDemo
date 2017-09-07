#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->timer=NULL;
}

MainWindow::~MainWindow()
{
    if(this->timer!=NULL)
    {
        delete timer;
    }
    delete ui;
}

void MainWindow::on_startBtn_clicked()
{
    if(this->timer==NULL)
    {
        this->timer=new QTimer;
        connect(timer,SIGNAL(timeout()),this,SLOT(screenSlots()));
        this->timer->start(((ui->ScreenTime->currentIndex()+1)*1000)/2);
    }
}

void MainWindow::screenSlots()
{
    pixmap=QPixmap::grabWindow(QApplication::desktop()->winId());
    QClipboard *clipboard=QApplication::clipboard();
    clipboard->setPixmap(pixmap);
    ui->ScreenLabel->setPixmap(pixmap.scaled(QSize(ui->ScreenLabel->width(),ui->ScreenLabel->height())));
}
