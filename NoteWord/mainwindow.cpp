#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("NoteWord");
    this->centerWindow();
    this->initSignalAndSlot();
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(QDir::currentPath()+"/赵雷 - 成都.mp3"));
    this->isPlay=false;
    this->player->stop();
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}

void MainWindow::initSignalAndSlot()
{
    connect(ui->newAction,SIGNAL(triggered(bool)),this,SLOT(newSlot()));
    connect(ui->openAction,SIGNAL(triggered(bool)),this,SLOT(openSlot()));
    connect(ui->aboutAction,SIGNAL(triggered(bool)),this,SLOT(aboutSlot()));
    connect(ui->allSelectAction,SIGNAL(triggered(bool)),this,SLOT(allSelectSlot()));
    connect(ui->colorAction,SIGNAL(triggered(bool)),this,SLOT(colorSlot()));
    connect(ui->copyAction,SIGNAL(triggered(bool)),this,SLOT(copySlot()));
    connect(ui->cutAction,SIGNAL(triggered(bool)),this,SLOT(cutSlot()));
    connect(ui->dateAction,SIGNAL(triggered(bool)),this,SLOT(dateSlot()));
    connect(ui->fontAction,SIGNAL(triggered(bool)),this,SLOT(fontSlot()));
    connect(ui->musicAction,SIGNAL(triggered(bool)),this,SLOT(musicSlot()));
    connect(ui->newSaveAction,SIGNAL(triggered(bool)),this,SLOT(newSaveSlot()));
    connect(ui->pasteAction,SIGNAL(triggered(bool)),this,SLOT(pasteSlot()));
    connect(ui->quitAction,SIGNAL(triggered(bool)),this,SLOT(quitSlot()));
    connect(ui->redoAction,SIGNAL(triggered(bool)),this,SLOT(redoSlot()));
    connect(ui->saveAction,SIGNAL(triggered(bool)),this,SLOT(saveSlot()));
    connect(ui->undoAction,SIGNAL(triggered(bool)),this,SLOT(undoSlot()));
    connect(ui->updateAction,SIGNAL(triggered(bool)),this,SLOT(updateSlot()));
    connect(ui->runAction,SIGNAL(triggered(bool)),this,SLOT(runSlot()));
}

void MainWindow::centerWindow()
{
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
}

void MainWindow::newSlot()
{
    ui->textEdit->clear();
    this->setWindowTitle("NoteWord");
}

void MainWindow::openSlot()
{
    QString fileName=QFileDialog::getOpenFileName(this,"打开",QDir::currentPath());
    if(fileName.isEmpty()||fileName.isNull())
    {
       QMessageBox::information(this,"提示","请选择一个文件");
    }
    else
    {
        QFile *file=new QFile(fileName);
        if(!file->open(QFileDevice::ReadOnly))
        {
            QMessageBox::information(this,"提示","打开文件失败");
            return;
        }
        this->setWindowTitle(fileName);
        QTextStream in(file);
        ui->textEdit->setText(in.readAll());
        delete file;
    }
}

void MainWindow::saveSlot()
{
    if(this->windowTitle()=="NoteWord")
    {
        newSaveSlot();
    }
    else
    {
       this->SaveFile(this->windowTitle());
    }
}

void MainWindow::newSaveSlot()
{
    QString fileName=QFileDialog::getSaveFileName(this,"保存",QDir::currentPath());
    if(fileName.isEmpty()||fileName.isNull())
    {
        QMessageBox::information(this,"提示","请填写一个文件名或选中一个文件");
    }
    else
    {
        this->SaveFile(fileName);
    }
}

void MainWindow::undoSlot()
{
    ui->textEdit->undo();
}

void MainWindow::redoSlot()
{
    ui->textEdit->redo();
}

void MainWindow::cutSlot()
{
    ui->textEdit->cut();
}

void MainWindow::copySlot()
{
    ui->textEdit->copy();
}

void MainWindow::allSelectSlot()
{
    ui->textEdit->selectAll();
}

void MainWindow::pasteSlot()
{
    ui->textEdit->paste();
}

void MainWindow::dateSlot()
{
    ui->textEdit->append(QDateTime::currentDateTime().toLocalTime().toString());
}

void MainWindow::fontSlot()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this,"字体");
    if (ok)
    {
        ui->textEdit->setFont(font);
    }
    else
    {
        QMessageBox::information(this,"提示","设置字体失败");
    }
}

void MainWindow::colorSlot()
{
    QColor color=QColorDialog::getColor(Qt::white,this,"颜色");
    ui->textEdit->setTextColor(color);
}

void MainWindow::aboutSlot()
{
    QAbout *about=new QAbout;
    about->show();
}

void MainWindow::quitSlot()
{
    this->close();
}

void MainWindow::musicSlot()
{
    if(isPlay)
    {
        player->stop();
        isPlay=false;
    }
    else
    {
        player->play();
        isPlay=true;
    }
}

void MainWindow::updateSlot()
{
    QDesktopServices::openUrl(QUrl("https://www.baidu.com"));
}

bool MainWindow::SaveFile(QString fileName)
{
    QFile *file=new QFile(fileName);
    if(!file->open(QFileDevice::WriteOnly))
    {
        QMessageBox::information(this,"提示","打开文件失败");
        return false;
    }
    QTextStream out(file);
    out<<ui->textEdit->toPlainText();
    QMessageBox::information(this,"提示","保存成功");
    this->setWindowTitle(fileName);
    delete file;
    return true;
}

 void MainWindow::closeEvent(QCloseEvent *event)
 {
     this->jugeSave();
     QMainWindow::closeEvent(event);
 }

 void MainWindow::jugeSave()
 {
     int iRet=QMessageBox::information(this,"提示","是否保存?",QMessageBox::Save|QMessageBox::Cancel);
     if(iRet==QMessageBox::Save)
     {
         this->saveSlot();
     }
 }

 void MainWindow::runSlot()
 {
     QRuner run;
     run.exec();
 }
