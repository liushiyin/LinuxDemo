#ifndef QMYLABEL_H
#define QMYLABEL_H
#include<QLabel>
#include<QPixmap>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QPainter>


class QMyLabel : public QLabel
{
public:
    QMyLabel();

    /*
     * 构造背景图片
     * @Param:
     *  QPixmap pixmap:
     */
    QMyLabel(const QPixmap& pixmap);

    /*
     * 获取背景图片
     * @return QPixmap:
     *  Label的背景图片
     */
    const QPixmap& getPixmap() const;

protected:
    void paintEvent(QPaintEvent * event);

signals:
   //鼠标按下
   void	mousePressEvent(QMouseEvent * ev);
   //鼠标释放
   void	mouseReleaseEvent(QMouseEvent * ev);

public slots:

private:
   //背景图片
    QPixmap BgPximap;

    //记录鼠标是否按下
    bool isMousePress;
};

#endif // QMYLABEL_H
