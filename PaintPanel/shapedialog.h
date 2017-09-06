#ifndef SHAPEDIALOG_H
#define SHAPEDIALOG_H
#include<QDialog>
#include<mylabel.h>
#include<QHBoxLayout>
#include<QTimer>

class ShapeDialog : public QDialog
{
    enum Shape_Type
    {
        Type_Line,
        Type_Rect,
        Type_Cirecle,
        Type_Triangle,
    };

protected:
    void	mousePressEvent(QMouseEvent * ev);
    void	mouseReleaseEvent(QMouseEvent * ev);

public:
    ShapeDialog();
    virtual ~ShapeDialog();

private:
    MyLabel *circleLabel;

    MyLabel *rectLabel;

    MyLabel *lineLabel;

    MyLabel *triangleLabel;

    Shape_Type type;

    QTimer *timer;
};

#endif // SHAPEDIALOG_H
