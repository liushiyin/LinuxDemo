#include "qrun.h"
#include "ui_qrun.h"

QRun::QRun(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QRun)
{
    ui->setupUi(this);
}

QRun::~QRun()
{
    delete ui;
}
