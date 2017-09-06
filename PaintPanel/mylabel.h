#ifndef MYLABEL_H
#define MYLABEL_H
#include<QLabel>
#include<QPaintEvent>
#include<QMouseEvent>
#include<QPainter>
#include<QPen>
#include<QRect>
#include<QDebug>

class MyLabel : public QLabel
{
public:
    MyLabel();

    const bool& getIsMousePress() const;

protected:
    //鼠标按下事件
    void	mousePressEvent(QMouseEvent * ev);
    //鼠标释放事件
    void	mouseReleaseEvent(QMouseEvent * ev);

private:
    bool isMousePress;
};

#endif // MYLABEL_H
