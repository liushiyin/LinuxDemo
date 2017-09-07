#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QApplication>
#include<QPixmap>
#include<QSize>
#include<QClipboard>
#include<QTimer>
#include<QDesktopWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startBtn_clicked();

    void screenSlots();

private:
    Ui::MainWindow *ui;
    QPixmap pixmap;
    QTimer * timer;
};

#endif // MAINWINDOW_H
