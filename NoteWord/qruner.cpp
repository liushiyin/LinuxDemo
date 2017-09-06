#include "qruner.h"
#include "ui_qruner.h"

QRuner::QRuner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRuner)
{
    ui->setupUi(this);
    this->setMaximumSize(352,181);
    this->setMinimumSize(352,181);
}

QRuner::~QRuner()
{
    delete ui;
}

void QRuner::on_okBtn_clicked()
{
      QProcess *myProcess = new QProcess();
      myProcess->start(ui->RunEdit->text());
      this->close();
}

void QRuner::on_cancelBtn_clicked()
{
    this->close();
}

void QRuner::on_RunEdit_returnPressed()
{
    on_okBtn_clicked();
}
