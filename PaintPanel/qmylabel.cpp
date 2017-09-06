#include "qmylabel.h"

QMyLabel::QMyLabel()
{
    this->isMousePress=false;
    this->update();
}

QMyLabel::QMyLabel(const QPixmap& pixmap)
{
    this->isMousePress=false;
    this->BgPximap=pixmap;
     this->setPixmap(this->BgPximap);
    this->update();
}

const QPixmap& QMyLabel::getPixmap() const
{
    return this->BgPximap;
}

void	QMyLabel::mouseReleaseEvent(QMouseEvent * ev)
{
    this->isMousePress=false;
    this->update();
     ev->accept();
}

void	QMyLabel::mousePressEvent(QMouseEvent * ev)
{
    this->isMousePress=true;
    this->update();
    ev->accept();
}

 void QMyLabel::paintEvent(QPaintEvent * event)
{
     QPainter painter(this);
     painter.setPen(Qt::blue);
     if(this->isMousePress)
     {
         painter.setBrush(Qt::SolidPattern);
         painter.drawRect(this->pos().x(),this->pos().y(),this->width(),this->height());
     }
     else
     {
         painter.setBrush(Qt::NoBrush);
        painter.drawRect(this->pos().x(),this->pos().y(),this->width(),this->height());
     }
     event->accept();
}






