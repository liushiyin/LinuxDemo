#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<QApplication>
#include<QDesktopWidget>
#include<QTimer>
#include<QPixmap>
#include<QFileDialog>
#include<QScreen>
#include<QFileDialog>
#include<QDir>
#include<QFile>
#include<QDesktopServices>
#include<QStandardPaths>
#include<QClipboard>
#include"catchdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void catchSelectScreen();

private slots:
    void on_catchScreenBtn_clicked();

    void on_saveScreen_clicked();

    void on_quitBtn_clicked();

    void catchScreen();

private:
    Ui::MainWindow *ui;
    QPixmap Pixmap;
    QTimer *timer;
    bool isPixmapClear;
};

#endif // MAINWINDOW_H
