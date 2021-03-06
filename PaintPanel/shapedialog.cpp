#include "shapedialog.h"

ShapeDialog::ShapeDialog()
{
    this->timer=new QTimer(this);
    this->circleLabel=new MyLabel;
    this->rectLabel=new MyLabel;
    this->lineLabel=new MyLabel;
    this->triangleLabel=new MyLabel;
    this->circleLabel->setMaximumSize(50,50);
    this->circleLabel->setMinimumSize(50,50);
    this->rectLabel->setMinimumSize(60,50);
    this->rectLabel->setMaximumSize(60,50);
    this->triangleLabel->setMinimumSize(40,50);
    this->triangleLabel->setMaximumSize(40,50);
    this->lineLabel->setMinimumSize(60,50);
    this->lineLabel->setMaximumSize(60,50);
    QHBoxLayout *hLayout=new QHBoxLayout;
    this->setLayout(hLayout);
    hLayout->addWidget(this->circleLabel);
    hLayout->addWidget(this->rectLabel);
    hLayout->addWidget(this->triangleLabel);
    hLayout->addWidget(this->lineLabel);
    this->setWindowTitle("选择形状");
    this->setMaximumSize(400,80);
    this->setMinimumSize(400,80);
    QPixmap pixmap("circle.png");
    QPixmap pixmap1("rectangle.png");
    QPixmap pixmap2("triangle.png");
    QPixmap pixmap3("line.png");
    this->circleLabel->setPixmap(pixmap.scaled(this->circleLabel->width(), this->circleLabel->height()));
    this->rectLabel->setPixmap(pixmap1.scaled(this->rectLabel->width(),this->rectLabel->height()));
    this->triangleLabel->setPixmap(pixmap2.scaled(this->triangleLabel->width(),this->triangleLabel->height()));
    this->lineLabel->setPixmap(pixmap3.scaled(this->lineLabel->width(),this->lineLabel->height()));
}

ShapeDialog::~ShapeDialog()
{
    delete timer;
}

void	ShapeDialog::mousePressEvent(QMouseEvent * ev)
{
    ev->accept();
}

void	ShapeDialog::mouseReleaseEvent(QMouseEvent * ev)
{
    qDebug()<<this->type<<"adasasf";
    ev->accept();
}
