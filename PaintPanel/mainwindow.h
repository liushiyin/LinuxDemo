#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPixmap>
#include<QFile>
#include<QFileDialog>
#include<QWidget>
#include<QPoint>
#include<vector>
#include<QLine>
#include<QRect>
#include<QPainter>
#include<QPen>
#include<QPaintEvent>
#include<QMouseEvent>
#include<QColorDialog>
#include<QFontDialog>
#include<QFont>
#include"shapedialog.h"
#include<QApplication>
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

protected:
    void mousePressEvent(QMouseEvent * event);
   void mouseReleaseEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);

private slots:
    void newActionSlot();

    void openActionSlot();

    void saveActionSlot();

    void newSaveActionSlot();

    void aboutActionSlot();

    void quitActionSlot();

    void cutActionSlot();

    void copyActionSlot();

    void pasteActionSlot();

    void selectActionSlot();

    void fillActionSlot();

    void fontActionSlot();

    void eraserActionSlot();

    void paintBrushSlot();

    void shapeActionSlot();

    void colorActionSlot();

    void rotateActionSlot();

    void resizeActionSlot();

private:
    /*
     * initSignalSlot()
     * 初始化信号和槽
     */
    void initSignalSlot();

    Ui::MainWindow *ui;

    QPixmap currentPixmap;

    bool isMousePress;

    QColor penColor;

    QFont textFont;
};

#endif // MAINWINDOW_H
