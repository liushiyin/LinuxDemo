#include "paintwidget.h"
#include "ui_paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintWidget)
{
    ui->setupUi(this);
}

PaintWidget::~PaintWidget()
{
    delete ui;
}
