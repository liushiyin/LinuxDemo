#ifndef QABOUT_H
#define QABOUT_H

#include <QWidget>
#include<QMovie>
#include<QApplication>
#include<QDesktopWidget>

namespace Ui {
class QAbout;
}

class QAbout : public QWidget
{
    Q_OBJECT

public:
    explicit QAbout(QWidget *parent = 0);
    ~QAbout();

private slots:
    void on_playBtn_clicked();

private:
    Ui::QAbout *ui;
    QMovie *movie;
};

#endif // QABOUT_H
