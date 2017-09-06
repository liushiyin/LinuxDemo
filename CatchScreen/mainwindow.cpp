#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isPixmapClear=true;
    ui->catchAllCheckBox->setChecked(true);
    ui->isHideCheckBox->setChecked(false);
    this->move((QApplication::desktop()->width()-this->width())/2,
               (QApplication::desktop()->height()-this->height())/2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_catchScreenBtn_clicked()
{

    if(ui->catchAllCheckBox->isChecked())
    {
        if(ui->isHideCheckBox->isChecked())
        {
            timer=new QTimer;
            connect(timer,SIGNAL(timeout()),this,SLOT(catchScreen()));
            timer->start(ui->delayComBox->currentIndex()*1000);
            this->hide();
        }
        else
        {
            this->catchScreen();
        }
    }
    else
    {
        this->catchSelectScreen();
    }
}

void MainWindow::on_saveScreen_clicked()
{
    if(!isPixmapClear)
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                    "../"+QDir::currentPath()+".jpg",
                                   tr("Images (*.png *.gif *.jpg *.bmp)"));
        if(!fileName.isEmpty())
        Pixmap.save(fileName);
        ui->SreeenLabel->clear();
        isPixmapClear=true;
     }
}

void MainWindow::on_quitBtn_clicked()
{
    this->close();
}

void MainWindow::catchScreen()
{
    isPixmapClear=false;
    QClipboard *clipbord=QApplication::clipboard();
    Pixmap=QPixmap::grabWindow(QApplication::desktop()->winId());
    ui->SreeenLabel->setPixmap(Pixmap.scaled(QSize(ui->SreeenLabel->width(),ui->SreeenLabel->height())));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(catchScreen()));
    clipbord->setPixmap(Pixmap);
    delete timer;
    this->show();
}

void MainWindow::catchSelectScreen()
{
    CatchDIalog catchDialog;
    this->hide();
    catchDialog.exec();
    Pixmap=catchDialog.getPixmap();
    if(Pixmap.isNull())
    {
        return;
    }
    if(Pixmap.height()>ui->SreeenLabel->height()||Pixmap.width()>ui->SreeenLabel->width())
    {
         ui->SreeenLabel->setPixmap(Pixmap.scaled(QSize(ui->SreeenLabel->width(),ui->SreeenLabel->height())));
    }
    else
    {
        ui->SreeenLabel->setPixmap(Pixmap);
    }
    isPixmapClear=false;
    this->show();
}

