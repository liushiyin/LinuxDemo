#ifndef CATCHDIALOG_H
#define CATCHDIALOG_H

#include <QDialog>
#include<QApplication>
#include<QDesktopWidget>
#include<QPainter>
#include<QPixmap>
#include<QDebug>
#include<QPoint>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QRect>

namespace Ui {
class CatchDIalog;
}

class CatchDIalog : public QDialog
{
    Q_OBJECT

public:
    explicit CatchDIalog(QWidget *parent = 0);
    ~CatchDIalog();

    QPixmap getPixmap();

protected:
    //鼠标按下事件
    virtual void	mousePressEvent(QMouseEvent * event);

    //鼠标释放事件
    virtual void	mouseReleaseEvent(QMouseEvent * event);

    //鼠标移动事件
    virtual void	mouseMoveEvent(QMouseEvent * event);

    //绘制事件
    void paintEvent(QPaintEvent *);

private:
    Ui::CatchDIalog *ui;

   void moveEvent(QMoveEvent *);

   bool isMousePress;

   //图片
   QPixmap pixmap;

   //记录鼠标按下时相对于整个屏幕的坐标
   QPoint globalFirst;

   //记录鼠标释放时相对于整个屏幕的坐标
   QPoint globalSecond;

   //鼠标按下时在客户区的坐标
   QPoint thisFirst;

   //鼠标释放时在客户区的坐标
   QPoint thisSecond;

   //需要绘制的矩形区域
   QRect rect;
};

#endif // CATCHDIALOG_H
