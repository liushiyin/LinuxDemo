#include "catchdialog.h"
#include "ui_catchdialog.h"

CatchDIalog::CatchDIalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatchDIalog)
{
    ui->setupUi(this);
     setWindowOpacity(0.5);
     isMousePress=false;
    this->setMaximumSize(QApplication::desktop()->width(),QApplication::desktop()->height());
    this->setMinimumSize(QApplication::desktop()->width(),QApplication::desktop()->height());
}

CatchDIalog::~CatchDIalog()
{
    delete ui;
}

 void  CatchDIalog::moveEvent(QMoveEvent *)
 {
     this->move(0,0);
 }

  QPixmap CatchDIalog::getPixmap()
  {
      return pixmap;
  }

  void CatchDIalog::mousePressEvent(QMouseEvent * event)
  {
      isMousePress=true;
      this->thisFirst.setX(event->x());
      this->thisFirst.setY(event->y());
      this->globalFirst.setX(event->globalX());
      this->globalFirst.setY(event->globalY());
  }

  void CatchDIalog::mouseReleaseEvent(QMouseEvent *event)
  {
      isMousePress=false;
      this->thisSecond.setX(event->x());
      this->thisSecond.setY(event->y());
      this->globalSecond.setX(event->globalX());
      this->globalSecond.setY(event->globalY());
      pixmap=QPixmap::grabWindow(QApplication::desktop()->winId(),globalFirst.x(),globalFirst.y(),globalSecond.x()-globalFirst.x(),globalSecond.y()-globalFirst.y());
      this->close();
  }

  void CatchDIalog::mouseMoveEvent(QMouseEvent * event)
  {
      if(isMousePress)
      {
          rect.setRect(thisFirst.x(),thisFirst.y(),event->x()-thisFirst.x(),event->y()-thisFirst.y());
          this->update();
      }
  }

  void CatchDIalog::paintEvent(QPaintEvent *)
  {
      QPainter painter(this);
      painter.setPen(Qt::red);
      painter.setBrush(Qt::SolidPattern);
      painter.drawRect(rect);
  }
