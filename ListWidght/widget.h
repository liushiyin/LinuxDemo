#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QListWidgetItem>
#include<QApplication>
#include<QDesktopWidget>
#include<QListView>
#include<QIcon>
#include<QDir>
#include<QFileInfo>
#include<QMessageBox>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_lineEdit_returnPressed();

    void on_addBtn_clicked();

    void on_deleteBtn_clicked();

    void	itemClicked(QListWidgetItem * item);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
