#include "mylabel.h"

MyLabel::MyLabel()
{
    isMousePress=false;
}

 void MyLabel::mousePressEvent(QMouseEvent * ev)
 {
     this->isMousePress=true;
     this->move(this->pos().x()+5,this->pos().y()+5);
     ev->accept();
 }

void	MyLabel::mouseReleaseEvent(QMouseEvent * ev)
{
    this->isMousePress=false;
    this->move(this->pos().x()-5,this->pos().y()-5);
    ev->accept();
}

const bool& MyLabel::getIsMousePress() const
{
   return isMousePress;
}
