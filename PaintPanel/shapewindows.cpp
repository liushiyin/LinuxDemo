#include "shapewindows.h"
#include "ui_shapewindows.h"

ShapeWindows::ShapeWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShapeWindows)
{
    ui->setupUi(this);
}

ShapeWindows::~ShapeWindows()
{
    delete ui;
}
