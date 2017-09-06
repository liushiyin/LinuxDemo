#include "selectshape.h"
#include "ui_selectshape.h"

SelectShape::SelectShape(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectShape)
{
    ui->setupUi(this);
    QGridLayout *layout=new QGridLayout(this);
    this->label=new QMyLabel;
    layout->addWidget(this->label);
    this->setLayout(layout);
}

SelectShape::~SelectShape()
{
    delete ui;
}
