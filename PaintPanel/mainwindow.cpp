#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->isMousePress=false;
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
    initSignalSlot();
}

void MainWindow::initSignalSlot()
{
   connect(ui->newAction,SIGNAL(triggered(bool)),this,SLOT(newActionSlot()));
   connect(ui->openAction,SIGNAL(triggered(bool)),this,SLOT(openActionSlot()));
   connect(ui->saveAction,SIGNAL(triggered(bool)),this,SLOT(saveActionSlot()));
   connect(ui->newSaveAction,SIGNAL(triggered(bool)),this,SLOT(newSaveActionSlot()));
   connect(ui->aboutAction,SIGNAL(triggered(bool)),this,SLOT(aboutActionSlot()));
   connect(ui->quitAction,SIGNAL(triggered(bool)),this,SLOT(quitActionSlot()));
   connect(ui->cutAction,SIGNAL(triggered(bool)),this,SLOT(cutActionSlot()));
   connect(ui->copyAction,SIGNAL(triggered(bool)),this,SLOT(copyActionSlot()));
   connect(ui->pasteAction,SIGNAL(triggered(bool)),this,SLOT(pasteActionSlot()));
   connect(ui->selectAction,SIGNAL(triggered(bool)),this,SLOT(selectActionSlot()));
   connect(ui->fillAction,SIGNAL(triggered(bool)),this,SLOT(fillActionSlot()));
   connect(ui->fontAction,SIGNAL(triggered(bool)),this,SLOT(fontActionSlot()));
   connect(ui->eraserAction,SIGNAL(triggered(bool)),this,SLOT(eraserActionSlot()));
   connect(ui->paintBrushAction,SIGNAL(triggered(bool)),this,SLOT(paintBrushSlot()));
   connect(ui->shapeAction,SIGNAL(triggered(bool)),this,SLOT(shapeActionSlot()));
   connect(ui->colorAction,SIGNAL(triggered(bool)),this,SLOT(colorActionSlot()));
   connect(ui->rotateAction,SIGNAL(triggered(bool)),this,SLOT(rotateActionSlot()));
   connect(ui->resizeAction,SIGNAL(triggered(bool)),this,SLOT(resizeActionSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newActionSlot()
{

}

void MainWindow::openActionSlot()
{

}

void MainWindow::saveActionSlot()
{

}

void MainWindow::newSaveActionSlot()
{

}

void MainWindow::aboutActionSlot()
{

}

void MainWindow::quitActionSlot()
{

}

void MainWindow::cutActionSlot()
{

}

void MainWindow::copyActionSlot()
{

}

void MainWindow::pasteActionSlot()
{

}

void MainWindow::selectActionSlot()
{

}

void MainWindow::fillActionSlot()
{

}

void MainWindow::fontActionSlot()
{
    bool ok;
    textFont = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
}

void MainWindow::eraserActionSlot()
{

}

void MainWindow::paintBrushSlot()
{

}

void MainWindow::shapeActionSlot()
{
    ShapeDialog dialog;
    dialog.exec();
}

void MainWindow::colorActionSlot()
{
    penColor=QColorDialog::getColor(Qt::white,this);
}

void MainWindow::rotateActionSlot()
{

}

void MainWindow::resizeActionSlot()
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->isMousePress=true;
    this->update();
    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    this->isMousePress=false;
    this->update();
    event->accept();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(this->isMousePress==true)
    {

    }
    else
    {

    }
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawLine(QPoint(0,40),QPoint(this->width(),40));
    painter.fillRect(QRect(0,44,this->width(),this->height()),Qt::white);
    event->accept();
}
