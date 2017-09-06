#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDesktopWidget>
#include<QApplication>
#include<QDir>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QString>
#include<QMessageBox>
#include<QFileDevice>
#include<QDateTime>
#include<QFontDialog>
#include<QFont>
#include<QColorDialog>
#include<QColor>
#include<QMediaPlayer>
#include<QDebug>
#include<QVideoWidget>
#include<QMediaPlaylist>
#include<QDesktopServices>
#include"qabout.h"
#include"qruner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //
     // cneterWindow()
     //窗口居中
    //
    void centerWindow();

private slots:
    //新建菜单栏的槽
    void newSlot();

    //打开菜单栏的槽
    void openSlot();

    //保存菜单栏的槽
    void saveSlot();

    //另存为菜单栏的槽
    void newSaveSlot();

    //撤销菜单栏的槽
    void undoSlot();

    //重做菜单栏的槽
    void redoSlot();

    //剪切菜单栏的槽
    void cutSlot();

    //拷贝菜单栏的槽
    void copySlot();

    //全选菜单栏的槽
    void allSelectSlot();

    //粘贴菜单栏的槽
    void pasteSlot();

    //日期菜单栏的槽
    void dateSlot();

    //字体菜单栏的槽
    void fontSlot();

    //颜色菜单栏的槽
    void colorSlot();

    //关于菜单栏的槽
    void aboutSlot();

    //退出菜单栏的槽
    void quitSlot();

    //音乐菜单栏的槽
    void musicSlot();

    //更新菜单栏的槽
    void updateSlot();

    //运行菜单栏的槽
    void runSlot();

private:
    //
    //初始化各个控件的信号和槽
    //
    void initSignalAndSlot();

    //
    //SaveFile(QString fileName)
    //保存文件
    //@Param
    //  QString fileName:所要保存的文件名
    //
    bool SaveFile(QString fileName);

    //
    //closeEvent(QCloseEvent *)
    //重写主窗口的关闭响应事件
    //@Param QCloseEvent *:
    //  关闭事件
    //
    void closeEvent(QCloseEvent *);

    //
    //jugeSave()
    //询问客户是否保存文件
    //
    void jugeSave();
private:
    Ui::MainWindow *ui;
     QMediaPlayer *player;
    bool isPlay;
};

#endif // MAINWINDOW_H
