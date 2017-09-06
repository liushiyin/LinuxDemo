#ifndef SHAPEWINDOWS_H
#define SHAPEWINDOWS_H

#include <QMainWindow>

namespace Ui {
class ShapeWindows;
}

class ShapeWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShapeWindows(QWidget *parent = 0);
    ~ShapeWindows();

private:
    Ui::ShapeWindows *ui;
};

#endif // SHAPEWINDOWS_H
