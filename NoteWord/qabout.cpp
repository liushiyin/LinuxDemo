#include "qabout.h"
#include "ui_qabout.h"

QAbout::QAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QAbout)
{
    ui->setupUi(this);
    this->setMaximumSize(483,328);
    this->setMinimumSize(483,328);
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
    this->movie=new QMovie("about.gif");
    ui->playLabel->setMovie(this->movie);
    this->movie->start();
}

QAbout::~QAbout()
{
    delete movie;
    delete ui;
}

void QAbout::on_playBtn_clicked()
{
    if(ui->playBtn->text()=="暂停")
    {
        this->movie->stop();
        ui->playBtn->setText("播放");
    }
    else
    {
        this->movie->start();
        ui->playBtn->setText("暂停");
    }
}
